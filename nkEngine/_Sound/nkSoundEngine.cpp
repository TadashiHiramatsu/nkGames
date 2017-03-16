/**
* サウンドエンジンクラスの実装
*/
#include"nkEngine/nkstdafx.h"
#include"nkSoundEngine.h"

#include"nkWaveFile.h"
#include"nkSoundSource.h"

#define NUM_PRESETS 30

namespace nkEngine
{
	namespace 
	{
		//マイクロソフトのサンプルから引っ張ってきたサウンドコーン。
		
		static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

		static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
		static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

		static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
		static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };

		XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
		{
			XAUDIO2FX_I3DL2_PRESET_FOREST,
			XAUDIO2FX_I3DL2_PRESET_DEFAULT,
			XAUDIO2FX_I3DL2_PRESET_GENERIC,
			XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
			XAUDIO2FX_I3DL2_PRESET_ROOM,
			XAUDIO2FX_I3DL2_PRESET_BATHROOM,
			XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
			XAUDIO2FX_I3DL2_PRESET_STONEROOM,
			XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
			XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
			XAUDIO2FX_I3DL2_PRESET_CAVE,
			XAUDIO2FX_I3DL2_PRESET_ARENA,
			XAUDIO2FX_I3DL2_PRESET_HANGAR,
			XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
			XAUDIO2FX_I3DL2_PRESET_HALLWAY,
			XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
			XAUDIO2FX_I3DL2_PRESET_ALLEY,
			XAUDIO2FX_I3DL2_PRESET_CITY,
			XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
			XAUDIO2FX_I3DL2_PRESET_QUARRY,
			XAUDIO2FX_I3DL2_PRESET_PLAIN,
			XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
			XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
			XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
			XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
			XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
			XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
			XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
			XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
			XAUDIO2FX_I3DL2_PRESET_PLATE,
		};
	}

	/**
	* 初期化.
	*/
	void CSoundEngine::Init()
	{

		//初期化関数?
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		unsigned int flag = 0;

#ifdef _DEBUG
		//デバッグ中である.
		flag |= XAUDIO2_DEBUG_ENGINE;
#endif

		HRESULT hr;

		//XAUDIO2を初期化.
		hr = XAudio2Create(&XAudio2_, flag);
		if (FAILED(hr))
		{
			NK_ASSERT(false, "Faild XAudio2Create");
			return;
		}

		//マスターボリューム作成.
		hr = XAudio2_->CreateMasteringVoice(&MasteringVoice_);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild CreateMasteringVoice");
			return;
		}


		XAUDIO2_DEVICE_DETAILS details;
		//サウンドデバイスの情報を取得.
		hr = XAudio2_->GetDeviceDetails(0, &details);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild GetDeviceDetails");
			return;
		}

		//チャンネルが規定値より多い?
		if (details.OutputFormat.Format.nChannels > OUTPUTCHANNELS)
		{
			Release();
			NK_ASSERT(false, "not enough channel");
			return;
		}

		//チャンネルマスクを設定.
		ChannnelMask_ = details.OutputFormat.dwChannelMask;
		//チャンネル数を設定.
		ChannelNum_ = details.OutputFormat.Format.nChannels;

		flag = 0;
#ifdef _DEBUG
		flag |= XAUDIO2FX_DEBUG;
#endif

		//リバーブエフェクトを作成。
		hr = XAudio2CreateReverb(&ReverbEffect_, flag);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild XAudio2CreateReverb");
			return;
		}

		XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { ReverbEffect_, TRUE, 1 } };
		XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

		//サブミックスボイスを作成.
		hr = XAudio2_->CreateSubmixVoice(
			&SubmixVoice_,
			1,
			details.OutputFormat.Format.nSamplesPerSec,
			0,0,nullptr,
			&effectChain);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild CreateSubmixVoice");
			return;
		}

		//デフォルトのFXパラメータを設定.
		XAUDIO2FX_REVERB_PARAMETERS native;
		ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
		//パラメータを設定.
		SubmixVoice_->SetEffectParameters(0, &native, sizeof(native));

		//3Dオーディオの初期化。
		const float SPEEDOFSOUND = X3DAUDIO_SPEED_OF_SOUND;
		X3DAudioInitialize(details.OutputFormat.dwChannelMask, SPEEDOFSOUND, X3DAudioHandle_);

		//リスナーの初期化.
		Listener_.Position = { 0.0f, 0.0f, 0.0f };
		Listener_.OrientFront = { 0.0f, 0.0f, 1.0f };
		Listener_.OrientTop = { 0.0f, 1.0f, 0.0f };

		//初期化完了。
		isInit = true;

	}

	/**
	* 更新.
	*/
	void CSoundEngine::Update()
	{

		if (!isInit)
		{
			//初期化されていない.
			return;
		}

		//サウンドリスナーの前方向を計算.
		if (Listener_.Position.x != ListenerPosition_.x ||
			Listener_.Position.z != ListenerPosition_.z) 
		{
			//リスナーがXZ平面上で動いている。
			
			//リスナーポジション.
			Vector3 listenerPos;
			listenerPos.Set(Listener_.Position);
			
			//角度を計算
			ListenerAngle_ = float(atan2(Listener_.OrientFront.x, Listener_.OrientFront.z));

			if (isListenerCone_ == true) 
			{
				Listener_.pCone = (X3DAUDIO_CONE*)&Listener_DirectionalCone;
			}
			else 
			{
				Listener_.pCone = nullptr;
			}

		}

		//タイムを取得.
		float deltaTime = Time().DeltaTime();

		if (deltaTime > 0.0f)
		{
			//リスナーの移動速度を計算する。
		
			Vector3 vel;
			vel.Set(Listener_.Position);
			vel.Sub(ListenerPosition_, vel);
			vel.Div(deltaTime);
			
			ListenerPosition_.CopyTo(Listener_.Position);
			vel.CopyTo(Listener_.Velocity);
		}

		DWORD dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER
			| X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB
			| X3DAUDIO_CALCULATE_REVERB;
		
		if (isRedirectToLFE_)
		{
			dwCalcFlags |= X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;
		}

		//3Dサウンドの計算。
		for (auto& soundsource : SoundSource3DList_)
		{
			X3DAUDIO_EMITTER emitter;

			emitter.pCone = &EmitterCone_;
			emitter.pCone->InnerAngle = 0.0f;
			emitter.pCone->OuterAngle = 0.0f;
			emitter.pCone->InnerVolume = 0.0f;
			emitter.pCone->OuterVolume = 1.0f;
			emitter.pCone->InnerLPF = 0.0f;
			emitter.pCone->OuterLPF = 1.0f;
			emitter.pCone->InnerReverb = 0.0f;
			emitter.pCone->OuterReverb = 1.0f;

			emitter.OrientFront = D3DXVECTOR3(0, 0, 1);
			emitter.OrientTop = D3DXVECTOR3(0, 1, 0);
			emitter.ChannelCount = INPUTCHANNELS;
			emitter.ChannelRadius = 1.0f;
			emitter.pChannelAzimuths = soundsource->GetEmitterAzimuth();

			emitter.InnerRadius = 2.0f;
			emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;;

			emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
			emitter.pLFECurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_LFE_Curve;
			emitter.pLPFDirectCurve = nullptr; // use default curve
			emitter.pLPFReverbCurve = nullptr; // use default curve
			emitter.pReverbCurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_Reverb_Curve;
			emitter.CurveDistanceScaler = 14.0f;
			emitter.DopplerScaler = 1.0f;

			soundsource->GetPosition().CopyTo(emitter.Position);
			soundsource->GetVelocity().CopyTo(emitter.Velocity);

			if (isInnerRadius_) 
			{
				emitter.InnerRadius = 2.0f;
				emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
			}
			else
			{
				emitter.InnerRadius = 0.0f;
				emitter.InnerRadiusAngle = 0.0f;
			}

			X3DAUDIO_DSP_SETTINGS* dspSettings = soundsource->GetDspSettings();
			X3DAudioCalculate(X3DAudioHandle_, &Listener_, &emitter, dwCalcFlags,dspSettings);

			IXAudio2SourceVoice* voice = soundsource->GetSourceVoice();
			
			if (voice != nullptr)
			{
				voice->SetFrequencyRatio(dspSettings->DopplerFactor);
				
				voice->SetOutputMatrix(MasteringVoice_, 
					soundsource->GetNumInputChannel(), 
					ChannelNum_,
					soundsource->GetMatrixCoefficient());
				
				voice->SetOutputMatrix(SubmixVoice_, 
					soundsource->GetNumInputChannel(),
					1,
					&dspSettings->ReverbLevel);

				XAUDIO2_FILTER_PARAMETERS FilterParametersDirect = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFDirectCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
				voice->SetOutputFilterParameters(MasteringVoice_, &FilterParametersDirect);
				XAUDIO2_FILTER_PARAMETERS FilterParametersReverb = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 6.0f * dspSettings->LPFReverbCoefficient), 1.0f }; // see XAudio2CutoffFrequencyToRadians() in XAudio2.h for more information on the formula used here
				voice->SetOutputFilterParameters(SubmixVoice_, &FilterParametersReverb);
			}

		}

	}

	/**
	* 解放.
	*/
	void CSoundEngine::Release()
	{
		//波形データをすべて解放.
		WaveFileBank_.ReleaseAll();

		if (XAudio2_ != nullptr)
		{
			XAudio2_->Release();
			XAudio2_ = nullptr;
		}

		//なんかクラッシュ
		/*if (MasteringVoice_ != nullptr)
		{
			MasteringVoice_->DestroyVoice();
			MasteringVoice_ = nullptr;
		}*/

		if (ReverbEffect_ != nullptr)
		{
			ReverbEffect_->Release();
			ReverbEffect_ = nullptr;
		}

		/*if (SubmixVoice_ != nullptr)
		{
			SubmixVoice_->DestroyVoice();
			SubmixVoice_ = nullptr;
		}*/

		CoUninitialize();

	}

	/**
	* XAudio2のソースボイスを作成.
	*
	* @param wavefile	波形データ.
	* @param is3Dsound	3Dサウンドフラグ.
	*/
	IXAudio2SourceVoice* CSoundEngine::CreateSourceVoice(WaveFile * wavefile, bool is3Dsound)
	{

		IXAudio2SourceVoice* sv;

		if (is3Dsound)
		{
			//3Dサウンド.

			XAUDIO2_SEND_DESCRIPTOR sendDescriptors[2];
			
			sendDescriptors[0].Flags = XAUDIO2_SEND_USEFILTER; // LPF direct-path
			sendDescriptors[0].pOutputVoice = SoundEngine().GetMasteringVoice();
			sendDescriptors[1].Flags = XAUDIO2_SEND_USEFILTER; // LPF reverb-path -- omit for better performance at the cost of less realistic occlusion
			sendDescriptors[1].pOutputVoice = SoundEngine().GetSubmixVoice();
			
			const XAUDIO2_VOICE_SENDS sendList = { 2, sendDescriptors };
			
			if (FAILED(XAudio2_->CreateSourceVoice(&sv, wavefile->GetFormat(), 0, 2.0f, nullptr, &sendList)))
			{
				NK_LOG("Failed CreateSourceVoice");
				return nullptr;
			}

		}
		else
		{
			//2Dサウンド.
			
			if (FAILED(XAudio2_->CreateSourceVoice(&sv, wavefile->GetFormat())))
			{
				NK_LOG("Failed CreateSourceVoice");
				return nullptr;
			}
		}

		return sv;

	}

}