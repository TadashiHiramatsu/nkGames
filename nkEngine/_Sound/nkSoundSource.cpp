/**
* �T�E���h�\�[�X�N���X�̎���
*/
#include"nkEngine/nkstdafx.h"
#include"nkSoundEngine.h"
#include"nkSoundSource.h"

namespace nkEngine
{

	/**
	* �I���������Đ������̏�����.
	*
	* @param filename	�t�@�C����.
	* @param is3Dsound	3D�T�E���h�t���O.
	*/
	void SoundSource::InitOnMemory(char * filename, bool is3Dsound)
	{
		WaveFile_ = SoundEngine().GetWaveFileBank().FindWaveFile(0, filename);

		if (!WaveFile_)
		{
			//�o�^����Ă��Ȃ��̂œǂݍ���.

			WaveFile_.reset(new WaveFile);
			WaveFile_->Open(filename);

			//wave�t�@�C���̃T�C�Y���̓ǂݍ��݃o�b�t�@���m�ۂ���
			WaveFile_->AllocReadBuffer(WaveFile_->GetSize());	
			
			//�g�`�f�[�^�o���N�ɓo�^.
			SoundEngine().GetWaveFileBank().SetWaveFile(0, WaveFile_);
			
			UINT dummy;
			WaveFile_->Read(WaveFile_->GetReadBuffer(), WaveFile_->GetSize(), &dummy);
			WaveFile_->ResetFile();

		}

		//�T�E���h�{�C�X�\�[�X���쐬�B
		SourceVoice_ = SoundEngine().CreateSourceVoice(WaveFile_.get(), is3Dsound);
		
		if (is3Dsound) 
		{
			SoundEngine().Add3DSoundSource(this);
		}

		InitCommon();

		is3DSound_ = is3Dsound;
	}

	/**
	* �X�g���[�~���O�Đ������̏�����.
	*
	* @param filename		�t�@�C����.
	* @param is3Dsound		3D�T�E���h�t���O.
	* @param ringbuffersize	�����O�o�b�t�@�̃T�C�Y.
	* @param bufferingsize	�X�g���[�~���O�̍ő�o�b�t�@�����O�T�C�Y.
	*/
	void SoundSource::InitStreaming(char * filename, bool is3Dsound, UINT ringbuffersize, UINT bufferingsize)
	{
		//�X�g���[�~���O��CWaveFile�̎g���܂킵�͂ł��Ȃ��B
		
		WaveFile_.reset(new WaveFile);
		WaveFile_->Open(filename);

		isStreaming_ = true;
		StreamingBufferSize_ = bufferingsize;
		WaveFile_->AllocReadBuffer(ringbuffersize);
		RingBufferSize_ = ringbuffersize;
		ReadStartPos_ = 0;
		CurrentBufferingSize_ = 0;

		//�T�E���h�{�C�X�\�[�X���쐬�B
		SourceVoice_ = SoundEngine().CreateSourceVoice(WaveFile_.get(), is3Dsound);
		
		if (is3Dsound) 
		{
			SoundEngine().Add3DSoundSource(this);
		}

		InitCommon();

		is3DSound_ = is3Dsound;
	}

	/**
	* �X�V.
	*/
	void SoundSource::Update()
	{
		if (isStreaming_) 
		{
			//�X�g���[�~���O�Đ����̍X�V�B
			UpdateStreaming();
		}
		else 
		{
			//�I���������Đ����̍X�V�����B
			UpdateOnMemory();
		}

		if (is3DSound_)
		{
			//�����̈ړ����x���X�V�B
			Velocity_.Sub(Position_, LastFramePosition_);
			Velocity_.Div(Time().DeltaTime());
			LastFramePosition_ = Position_;
		}
	}
	
	/**
	* ���.
	*/
	void SoundSource::Release()
	{
		
		//�X�g���[�~���O�Đ��̏ꍇ�͉��
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
	* �Đ�.
	*
	* @param isLoop	���[�v�Đ��t���O.
	*/
	void SoundSource::Play(bool isLoop)
	{
		if (isPlaying_)
		{
			//�Đ����̂��̂��ĊJ����B
			SourceVoice_->Start(0);
		}
		else 
		{
			if (isStreaming_) 
			{
				//�o�b�t�@�����O�J�n
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
	* ���ʂ̏�����.
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
	* �I���������Đ����̍X�V����.
	*/
	void SoundSource::UpdateOnMemory()
	{
		if (!isPlaying_)
		{
			//�Đ����ł͂Ȃ�.
			return;
		}

		XAUDIO2_VOICE_STATE state;
		SourceVoice_->GetState(&state);
		if (state.BuffersQueued <= 0)
		{
			isPlaying_ = false;
			if (isLoop_)
			{
				//���[�v�B
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
	* �X�g���[�~���O�Đ����̍X�V����.
	*/
	void SoundSource::UpdateStreaming()
	{
		if (!isPlaying_)
		{
			return;
		}

		if (StreamingState_ == StreamingStateE::StreamingBuffering)
		{
			//�o�b�t�@�����O���B
			if (WaveFile_->IsReadEnd()) 
			{
				//�o�b�t�@�����O���I������B
				StreamingState_ = StreamingStateE::StreamingQueueing;
			}
		}
		if (StreamingState_ == StreamingStateE::StreamingQueueing)
		{
			//�L���[�C���O���B
			XAUDIO2_VOICE_STATE state;
			SourceVoice_->GetState(&state);
			if (state.BuffersQueued <= 2) 
			{
				//�L���[�C���O����Ă���o�b�t�@���Q�ȉ��ɂȂ�����L���[�C���O�ł���B
				
				char* buff = WaveFile_->GetReadBuffer();
				Play(&buff[ReadStartPos_], CurrentBufferingSize_);

				if (CurrentBufferingSize_ == 0) 
				{
					//�ǂݍ��񂾃T�C�Y���O�Ƃ������Ƃ͖��[�܂œǂݍ��݂��I������Ƃ������ƁB
					if (isLoop_)
					{
						//���[�v����H
						//wave�t�@�C���̓ǂݍ��݈ʒu�����Z�b�g���ăo�b�t�@�����O�ĊJ�B
						WaveFile_->ResetFile();
						StartStreamingBuffring();
					}
					else 
					{
						//���[�v���Ȃ��ꍇ�̓L���[����ɂȂ�����Đ��I���B
						if (state.BuffersQueued == 0) 
						{
							//�Đ��I���B
							isPlaying_ = false;
							DeleteGO(this);
							Remove3DSound();
						}
					}
				}
				else 
				{
					//�����o�b�t�@�����O����B
					StartStreamingBuffring();
				}
			}
		}
	}

	/**
	* �Đ�?
	*
	* @param buffer		�o�b�t�@.
	* @param buffersizr	�o�b�t�@�T�C�Y.
	*/
	void SoundSource::Play(char * buffer, UINT buffersize)
	{
		XAUDIO2_BUFFER Buffer = { 0 };
		Buffer.pAudioData = (BYTE*)buffer;
		Buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		Buffer.AudioBytes = buffersize;

		if (SourceVoice_ != nullptr && buffersize > 0) 
		{
			//�Đ��J�n�B
			if (FAILED(SourceVoice_->SubmitSourceBuffer(&Buffer)))
			{
				Release();
				NK_LOG("Failed SourceVoice_->SubmitSourceBuffer");
				return;
			}
		}

	}

	/**
	* �X�g���[�~���O�o�b�t�@�����O�̊J�n.
	*/
	void SoundSource::StartStreamingBuffring()
	{
		char* readStartBuff = WaveFile_->GetReadBuffer();

		ReadStartPos_ += CurrentBufferingSize_;
		if (ReadStartPos_ + StreamingBufferSize_ >= RingBufferSize_) 
		{
			//�����O�o�b�t�@�̃T�C�Y�𒴂���B
			//�z����B
			ReadStartPos_ = 0;
		}

		WaveFile_->ReadAsync(&readStartBuff[ReadStartPos_], StreamingBufferSize_, &CurrentBufferingSize_);
		StreamingState_ = StreamingStateE::StreamingBuffering;
	}

	/**
	* 3D�T�E���h�̍폜.
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