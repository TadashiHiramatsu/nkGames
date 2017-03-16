/**
* サウンドソースクラスの定義.
*/
#pragma once

#include"nkWaveFile.h"

namespace nkEngine
{

	/**
	* サウンドソースクラス.
	*/
	class SoundSource : public IGameObject
	{
	private:

		/** ストリーミング再生の状態. */
		enum class StreamingStateE
		{
			StreamingBuffering,	//!< バッファリング中。
			StreamingQueueing,	//!< キューイング中。
		};

	public:

		/**
		* コンストラクタ.
		*/
		SoundSource()
		{
			memset(EmitterAzimuth_, 0, sizeof(EmitterAzimuth_));
			memset(MatrixCoefficient_, 0, sizeof(MatrixCoefficient_));
		}

		/**
		* デストラクタ.
		*/
		~SoundSource()
		{
			Release();
		}

		/**
		* オンメモリ再生向けの初期化.
		*
		* @param filename	ファイル名.
		* @param is3Dsound	3Dサウンドフラグ.
		*/
		void InitOnMemory(char* filename, bool is3Dsound = false);

		/**
		* ストリーミング再生向けの初期化.
		* 
		* @param filename		ファイル名.
		* @param is3Dsound		3Dサウンドフラグ.
		* @param ringbuffersize	リングバッファのサイズ.
		* @param bufferingsize	ストリーミングの最大バッファリングサイズ.
		*/
		void InitStreaming(char* filename,bool is3Dsound = false,UINT ringbuffersize = 3 * 1024 * 1024,UINT bufferingsize = 1024 * 512);

		/** 
		* 更新. 
		*/
		void Update();

		/**
		* 解放.
		*/
		void Release();

		/**
		* 再生.
		*
		* @param isLoop	ループ再生フラグ.
		*/
		void Play(bool isLoop = false);

		/**
		* 停止.
		*/
		void Stop()
		{
			SourceVoice_->Stop();
			isPlaying_ = false;
		}

		/**
		* 一時停止.
		*/
		void Pause()
		{
			SourceVoice_->Stop();
		}

		/**
		* 再生中フラグを取得.
		*/
		bool IsPlaying() const
		{
			return isPlaying_;
		}

		/**
		* ボリュームを設定.
		*
		* @param vol	ボリューム.
		*/
		void SetVolume(float vol)
		{
			SourceVoice_->SetVolume(vol);
		}

		/**
		* 音源の座標を設定.
		*
		*
		* @param pos	座標.
		*/
		void SetPosition(const Vector3& pos)
		{
			Position_ = pos;
			if (isSetPositionFirst_)
			{
				LastFramePosition_ = Position_;
				isSetPositionFirst_ = false;
			}
		}
		
		/**
		* 座標を取得.
		*/
		const Vector3& GetPosition() const
		{
			return Position_;
		}

		/**
		* 移動速度を取得.
		*/
		const Vector3& GetVelocity() const
		{
			return Velocity_;
		}

		/**
		* ループフラグを取得.
		*/
		bool IsLoop() const
		{
			return isLoop_;
		}

		/**
		* ボイスの周波数調整比.
		*
		* @param ratio	周波数比.
		*/
		void SetFrequencyRatio(float ratio)
		{
			if (SourceVoice_ != nullptr)
			{
				SourceVoice_->SetFrequencyRatio(ratio);
			}
		}

		/**
		* ソースボイスの取得.
		*/
		IXAudio2SourceVoice* GetSourceVoice() const
		{
			return SourceVoice_;
		}

		/**
		* 入力チャンネル数を取得.
		*/
		int GetNumInputChannel() const
		{
			return WaveFile_->GetFormat()->nChannels;
		}

		/**
		* エミッターの包囲角を取得.
		*/
		FLOAT32* GetEmitterAzimuth() 
		{
			return EmitterAzimuth_;
		}

		/**
		* 係数行列を取得.
		*/
		FLOAT32* GetMatrixCoefficient() 
		{
			return MatrixCoefficient_;
		}

		/**
		* DSPセッティング?を取得.
		*/
		X3DAUDIO_DSP_SETTINGS* GetDspSettings()
		{
			return &DspSettings_;
		}

	private:

		/**
		* 共通の初期化.
		*/
		void InitCommon();

		/**
		* オンメモリ再生中の更新処理.
		*/
		void UpdateOnMemory();

		/**
		* ストリーミング再生中の更新処理.
		*/
		void UpdateStreaming();

		/**
		* 再生?
		*
		* @param buffer		バッファ.
		* @param buffersizr	バッファサイズ.
		*/
		void Play(char* buffer, UINT buffersize);

		/**
		* ストリーミングバッファリングの開始.
		*/
		void StartStreamingBuffring();

		/**
		* 3Dサウンドの削除.
		*/
		void Remove3DSound();

	private:

		/** 波形データクラス. */
		shared_ptr<WaveFile> WaveFile_;
		/** ソースボイス. */
		IXAudio2SourceVoice* SourceVoice_ = nullptr;
		
		/** ループフラグ. */
		bool isLoop_ = false;
		/** 再生中フラグ. */
		bool isPlaying_ = false;

		/** ストリーミング再生フラグ. */
		bool isStreaming_ = false;
		/** ストリーミング用のバッファリングサイズ. */
		UINT StreamingBufferSize_ = 0;
		/** 現在のバッファリングのサイズ. */
		UINT CurrentBufferingSize_ = 0;
		/** 読み込み開始位置. */
		UINT ReadStartPos_ = 0;
		/** リングバッファのサイズ. */
		UINT RingBufferSize_ = 0;

		/** ストリーミングステータス. */
		StreamingStateE	StreamingState_ = StreamingStateE::StreamingBuffering;
		
		/** 3Dサウンドフラグ. */
		bool is3DSound_ = false;
		/** 音源の座標. */
		Vector3 Position_ = Vector3::Zero;
		/** 音源の1フレーム前の座標. */
		Vector3 LastFramePosition_ = Vector3::Zero;
		/** 移動速度. */
		Vector3 Velocity_ = Vector3::Zero;

		/** エミッターの包囲角. */
		FLOAT32 EmitterAzimuth_[INPUTCHANNELS];
		/** 係数行列. */
		FLOAT32 MatrixCoefficient_[INPUTCHANNELS * OUTPUTCHANNELS];
		/** DSPセッティング? */
		X3DAUDIO_DSP_SETTINGS DspSettings_;

		/** 一番最初のsetPositionフラグ. */
		bool isSetPositionFirst_ = true;

	};

}