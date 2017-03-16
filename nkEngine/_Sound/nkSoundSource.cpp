/**
* サウンドソースクラスの実装
*/
#include"nkEngine/nkstdafx.h"
#include"nkSoundEngine.h"
#include"nkSoundSource.h"

namespace nkEngine
{

	/**
	* オンメモリ再生向けの初期化.
	*
	* @param filename	ファイル名.
	* @param is3Dsound	3Dサウンドフラグ.
	*/
	void SoundSource::InitOnMemory(char * filename, bool is3Dsound)
	{
		WaveFile_ = SoundEngine().GetWaveFileBank().FindWaveFile(0, filename);

		if (!WaveFile_)
		{
			//登録されていないので読み込み.

			WaveFile_.reset(new WaveFile);
			WaveFile_->Open(filename);

			//waveファイルのサイズ分の読み込みバッファを確保する
			WaveFile_->AllocReadBuffer(WaveFile_->GetSize());	
			
			//波形データバンクに登録.
			SoundEngine().GetWaveFileBank().SetWaveFile(0, WaveFile_);
			
			UINT dummy;
			WaveFile_->Read(WaveFile_->GetReadBuffer(), WaveFile_->GetSize(), &dummy);
			WaveFile_->ResetFile();

		}

		//サウンドボイスソースを作成。
		SourceVoice_ = SoundEngine().CreateSourceVoice(WaveFile_.get(), is3Dsound);
		
		if (is3Dsound) 
		{
			SoundEngine().Add3DSoundSource(this);
		}

		InitCommon();

		is3DSound_ = is3Dsound;
	}

	/**
	* ストリーミング再生向けの初期化.
	*
	* @param filename		ファイル名.
	* @param is3Dsound		3Dサウンドフラグ.
	* @param ringbuffersize	リングバッファのサイズ.
	* @param bufferingsize	ストリーミングの最大バッファリングサイズ.
	*/
	void SoundSource::InitStreaming(char * filename, bool is3Dsound, UINT ringbuffersize, UINT bufferingsize)
	{
		//ストリーミングはCWaveFileの使いまわしはできない。
		
		WaveFile_.reset(new WaveFile);
		WaveFile_->Open(filename);

		isStreaming_ = true;
		StreamingBufferSize_ = bufferingsize;
		WaveFile_->AllocReadBuffer(ringbuffersize);
		RingBufferSize_ = ringbuffersize;
		ReadStartPos_ = 0;
		CurrentBufferingSize_ = 0;

		//サウンドボイスソースを作成。
		SourceVoice_ = SoundEngine().CreateSourceVoice(WaveFile_.get(), is3Dsound);
		
		if (is3Dsound) 
		{
			SoundEngine().Add3DSoundSource(this);
		}

		InitCommon();

		is3DSound_ = is3Dsound;
	}

	/**
	* 更新.
	*/
	void SoundSource::Update()
	{
		if (isStreaming_) 
		{
			//ストリーミング再生中の更新。
			UpdateStreaming();
		}
		else 
		{
			//オンメモリ再生中の更新処理。
			UpdateOnMemory();
		}

		if (is3DSound_)
		{
			//音源の移動速度を更新。
			Velocity_.Sub(Position_, LastFramePosition_);
			Velocity_.Div(Time().DeltaTime());
			LastFramePosition_ = Position_;
		}
	}
	
	/**
	* 解放.
	*/
	void SoundSource::Release()
	{
		
		//ストリーミング再生の場合は解放
		if (isStreaming_)
		{
			WaveFile_->Release();
		}

		if (SourceVoice_ != nullptr) 
		{
			SourceVoice_->DestroyVoice();
			SourceVoice_ = nullptr;
		}

		Remove3DSound();
		DeleteGO(this);
	
	}

	/**
	* 再生.
	*
	* @param isLoop	ループ再生フラグ.
	*/
	void SoundSource::Play(bool isLoop)
	{
		if (isPlaying_)
		{
			//再生中のものを再開する。
			SourceVoice_->Start(0);
		}
		else 
		{
			if (isStreaming_) 
			{
				//バッファリング開始
				WaveFile_->ResetFile();
				StartStreamingBuffring();
				SourceVoice_->Start(0, 0);
			}
			else
			{
				SourceVoice_->FlushSourceBuffers();
				SourceVoice_->Start(0);
				Play(WaveFile_->GetReadBuffer(), WaveFile_->GetSize());
			}
			isPlaying_ = true;
		}
		isLoop_ = isLoop;
	}

	/**
	* 共通の初期化.
	*/
	void SoundSource::InitCommon()
	{
		DspSettings_.SrcChannelCount = INPUTCHANNELS;
		DspSettings_.DstChannelCount = SoundEngine().GetChannelNum();
		DspSettings_.pMatrixCoefficients = MatrixCoefficient_;
		DspSettings_.pDelayTimes = nullptr;
		DspSettings_.DopplerFactor = 1.0f;
		DspSettings_.LPFDirectCoefficient = 0.82142854f;
		DspSettings_.LPFReverbCoefficient = 0.75f;
		DspSettings_.ReverbLevel = 0.69114286f;
		DspSettings_.EmitterToListenerAngle = 0.0f;
		DspSettings_.EmitterToListenerDistance = 10.0f;
		DspSettings_.EmitterVelocityComponent = 0.0f;
		DspSettings_.ListenerVelocityComponent = 0.0f;
	}

	/**
	* オンメモリ再生中の更新処理.
	*/
	void SoundSource::UpdateOnMemory()
	{
		if (!isPlaying_)
		{
			//再生中ではない.
			return;
		}

		XAUDIO2_VOICE_STATE state;
		SourceVoice_->GetState(&state);
		if (state.BuffersQueued <= 0)
		{
			isPlaying_ = false;
			if (isLoop_)
			{
				//ループ。
				Play(isLoop_);
			}
			else 
			{
				DeleteGO(this);
				Remove3DSound();
			}
		}
	}

	/**
	* ストリーミング再生中の更新処理.
	*/
	void SoundSource::UpdateStreaming()
	{
		if (!isPlaying_)
		{
			return;
		}

		if (StreamingState_ == StreamingStateE::StreamingBuffering)
		{
			//バッファリング中。
			if (WaveFile_->IsReadEnd()) 
			{
				//バッファリングが終わった。
				StreamingState_ = StreamingStateE::StreamingQueueing;
			}
		}
		if (StreamingState_ == StreamingStateE::StreamingQueueing)
		{
			//キューイング中。
			XAUDIO2_VOICE_STATE state;
			SourceVoice_->GetState(&state);
			if (state.BuffersQueued <= 2) 
			{
				//キューイングされているバッファが２以下になったらキューイングできる。
				
				char* buff = WaveFile_->GetReadBuffer();
				Play(&buff[ReadStartPos_], CurrentBufferingSize_);

				if (CurrentBufferingSize_ == 0) 
				{
					//読み込んだサイズが０ということは末端まで読み込みが終わったということ。
					if (isLoop_)
					{
						//ループする？
						//waveファイルの読み込み位置をリセットしてバッファリング再開。
						WaveFile_->ResetFile();
						StartStreamingBuffring();
					}
					else 
					{
						//ループしない場合はキューが空になったら再生終了。
						if (state.BuffersQueued == 0) 
						{
							//再生終了。
							isPlaying_ = false;
							DeleteGO(this);
							Remove3DSound();
						}
					}
				}
				else 
				{
					//次をバッファリングする。
					StartStreamingBuffring();
				}
			}
		}
	}

	/**
	* 再生?
	*
	* @param buffer		バッファ.
	* @param buffersizr	バッファサイズ.
	*/
	void SoundSource::Play(char * buffer, UINT buffersize)
	{
		XAUDIO2_BUFFER Buffer = { 0 };
		Buffer.pAudioData = (BYTE*)buffer;
		Buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		Buffer.AudioBytes = buffersize;

		if (SourceVoice_ != nullptr && buffersize > 0) 
		{
			//再生開始。
			if (FAILED(SourceVoice_->SubmitSourceBuffer(&Buffer)))
			{
				Release();
				NK_LOG("Failed SourceVoice_->SubmitSourceBuffer");
				return;
			}
		}

	}

	/**
	* ストリーミングバッファリングの開始.
	*/
	void SoundSource::StartStreamingBuffring()
	{
		char* readStartBuff = WaveFile_->GetReadBuffer();

		ReadStartPos_ += CurrentBufferingSize_;
		if (ReadStartPos_ + StreamingBufferSize_ >= RingBufferSize_) 
		{
			//リングバッファのサイズを超える。
			//循環する。
			ReadStartPos_ = 0;
		}

		WaveFile_->ReadAsync(&readStartBuff[ReadStartPos_], StreamingBufferSize_, &CurrentBufferingSize_);
		StreamingState_ = StreamingStateE::StreamingBuffering;
	}

	/**
	* 3Dサウンドの削除.
	*/
	void SoundSource::Remove3DSound()
	{
		if (is3DSound_)
		{
			SoundEngine().Remove3DSoundSource(this);
			is3DSound_ = false;
		}
	}

}