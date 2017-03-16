/**
* �T�E���h�G���W���N���X�̎���
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
		//�}�C�N���\�t�g�̃T���v��������������Ă����T�E���h�R�[���B
		
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
	* ������.
	*/
	void CSoundEngine::Init()
	{

		//�������֐�?
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		unsigned int flag = 0;

#ifdef _DEBUG
		//�f�o�b�O���ł���.
		flag |= XAUDIO2_DEBUG_ENGINE;
#endif

		HRESULT hr;

		//XAUDIO2��������.
		hr = XAudio2Create(&XAudio2_, flag);
		if (FAILED(hr))
		{
			NK_ASSERT(false, "Faild XAudio2Create");
			return;
		}

		//�}�X�^�[�{�����[���쐬.
		hr = XAudio2_->CreateMasteringVoice(&MasteringVoice_);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild CreateMasteringVoice");
			return;
		}


		XAUDIO2_DEVICE_DETAILS details;
		//�T�E���h�f�o�C�X�̏����擾.
		hr = XAudio2_->GetDeviceDetails(0, &details);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild GetDeviceDetails");
			return;
		}

		//�`�����l�����K��l��葽��?
		if (details.OutputFormat.Format.nChannels > OUTPUTCHANNELS)
		{
			Release();
			NK_ASSERT(false, "not enough channel");
			return;
		}

		//�`�����l���}�X�N��ݒ�.
		ChannnelMask_ = details.OutputFormat.dwChannelMask;
		//�`�����l������ݒ�.
		ChannelNum_ = details.OutputFormat.Format.nChannels;

		flag = 0;
#ifdef _DEBUG
		flag |= XAUDIO2FX_DEBUG;
#endif

		//���o�[�u�G�t�F�N�g���쐬�B
		hr = XAudio2CreateReverb(&ReverbEffect_, flag);
		if (FAILED(hr))
		{
			Release();
			NK_ASSERT(false, "Faild XAudio2CreateReverb");
			return;
		}

		XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { ReverbEffect_, TRUE, 1 } };
		XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

		//�T�u�~�b�N�X�{�C�X���쐬.
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

		//�f�t�H���g��FX�p�����[�^��ݒ�.
		XAUDIO2FX_REVERB_PARAMETERS native;
		ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
		//�p�����[�^��ݒ�.
		SubmixVoice_->SetEffectParameters(0, &native, sizeof(native));

		//3D�I�[�f�B�I�̏������B
		const float SPEEDOFSOUND = X3DAUDIO_SPEED_OF_SOUND;
		X3DAudioInitialize(details.OutputFormat.dwChannelMask, SPEEDOFSOUND, X3DAudioHandle_);

		//���X�i�[�̏�����.
		Listener_.Position = { 0.0f, 0.0f, 0.0f };
		Listener_.OrientFront = { 0.0f, 0.0f, 1.0f };
		Listener_.OrientTop = { 0.0f, 1.0f, 0.0f };

		//�����������B
		isInit = true;

	}

	/**
	* �X�V.
	*/
	void CSoundEngine::Update()
	{

		if (!isInit)
		{
			//����������Ă��Ȃ�.
			return;
		}

		//�T�E���h���X�i�[�̑O�������v�Z.
		if (Listener_.Position.x != ListenerPosition_.x ||
			Listener_.Position.z != ListenerPosition_.z) 
		{
			//���X�i�[��XZ���ʏ�œ����Ă���B
			
			//���X�i�[�|�W�V����.
			Vector3 listenerPos;
			listenerPos.Set(Listener_.Position);
			
			//�p�x���v�Z
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

		//�^�C�����擾.
		float deltaTime = Time().DeltaTime();

		if (deltaTime > 0.0f)
		{
			//���X�i�[�̈ړ����x���v�Z����B
		
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

		//3D�T�E���h�̌v�Z�B
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
	* ���.
	*/
	void CSoundEngine::Release()
	{
		//�g�`�f�[�^�����ׂĉ��.
		WaveFileBank_.ReleaseAll();

		if (XAudio2_ != nullptr)
		{
			XAudio2_->Release();
			XAudio2_ = nullptr;
		}

		//�Ȃ񂩃N���b�V��
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
	* XAudio2�̃\�[�X�{�C�X���쐬.
	*
	* @param wavefile	�g�`�f�[�^.
	* @param is3Dsound	3D�T�E���h�t���O.
	*/
	IXAudio2SourceVoice* CSoundEngine::CreateSourceVoice(WaveFile * wavefile, bool is3Dsound)
	{

		IXAudio2SourceVoice* sv;

		if (is3Dsound)
		{
			//3D�T�E���h.

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
			//2D�T�E���h.
			
			if (FAILED(XAudio2_->CreateSourceVoice(&sv, wavefile->GetFormat())))
			{
				NK_LOG("Failed CreateSourceVoice");
				return nullptr;
			}
		}

		return sv;

	}

}