/**
* �T�E���h�\�[�X�N���X�̒�`.
*/
#pragma once

#include"nkWaveFile.h"

namespace nkEngine
{

	/**
	* �T�E���h�\�[�X�N���X.
	*/
	class SoundSource : public IGameObject
	{
	private:

		/** �X�g���[�~���O�Đ��̏��. */
		enum class StreamingStateE
		{
			StreamingBuffering,	//!< �o�b�t�@�����O���B
			StreamingQueueing,	//!< �L���[�C���O���B
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		SoundSource()
		{
			memset(EmitterAzimuth_, 0, sizeof(EmitterAzimuth_));
			memset(MatrixCoefficient_, 0, sizeof(MatrixCoefficient_));
		}

		/**
		* �f�X�g���N�^.
		*/
		~SoundSource()
		{
			Release();
		}

		/**
		* �I���������Đ������̏�����.
		*
		* @param filename	�t�@�C����.
		* @param is3Dsound	3D�T�E���h�t���O.
		*/
		void InitOnMemory(char* filename, bool is3Dsound = false);

		/**
		* �X�g���[�~���O�Đ������̏�����.
		* 
		* @param filename		�t�@�C����.
		* @param is3Dsound		3D�T�E���h�t���O.
		* @param ringbuffersize	�����O�o�b�t�@�̃T�C�Y.
		* @param bufferingsize	�X�g���[�~���O�̍ő�o�b�t�@�����O�T�C�Y.
		*/
		void InitStreaming(char* filename,bool is3Dsound = false,UINT ringbuffersize = 3 * 1024 * 1024,UINT bufferingsize = 1024 * 512);

		/** 
		* �X�V. 
		*/
		void Update();

		/**
		* ���.
		*/
		void Release();

		/**
		* �Đ�.
		*
		* @param isLoop	���[�v�Đ��t���O.
		*/
		void Play(bool isLoop = false);

		/**
		* ��~.
		*/
		void Stop()
		{
			SourceVoice_->Stop();
			isPlaying_ = false;
		}

		/**
		* �ꎞ��~.
		*/
		void Pause()
		{
			SourceVoice_->Stop();
		}

		/**
		* �Đ����t���O���擾.
		*/
		bool IsPlaying() const
		{
			return isPlaying_;
		}

		/**
		* �{�����[����ݒ�.
		*
		* @param vol	�{�����[��.
		*/
		void SetVolume(float vol)
		{
			SourceVoice_->SetVolume(vol);
		}

		/**
		* �����̍��W��ݒ�.
		*
		*
		* @param pos	���W.
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
		* ���W���擾.
		*/
		const Vector3& GetPosition() const
		{
			return Position_;
		}

		/**
		* �ړ����x���擾.
		*/
		const Vector3& GetVelocity() const
		{
			return Velocity_;
		}

		/**
		* ���[�v�t���O���擾.
		*/
		bool IsLoop() const
		{
			return isLoop_;
		}

		/**
		* �{�C�X�̎��g��������.
		*
		* @param ratio	���g����.
		*/
		void SetFrequencyRatio(float ratio)
		{
			if (SourceVoice_ != nullptr)
			{
				SourceVoice_->SetFrequencyRatio(ratio);
			}
		}

		/**
		* �\�[�X�{�C�X�̎擾.
		*/
		IXAudio2SourceVoice* GetSourceVoice() const
		{
			return SourceVoice_;
		}

		/**
		* ���̓`�����l�������擾.
		*/
		int GetNumInputChannel() const
		{
			return WaveFile_->GetFormat()->nChannels;
		}

		/**
		* �G�~�b�^�[�̕�͊p���擾.
		*/
		FLOAT32* GetEmitterAzimuth() 
		{
			return EmitterAzimuth_;
		}

		/**
		* �W���s����擾.
		*/
		FLOAT32* GetMatrixCoefficient() 
		{
			return MatrixCoefficient_;
		}

		/**
		* DSP�Z�b�e�B���O?���擾.
		*/
		X3DAUDIO_DSP_SETTINGS* GetDspSettings()
		{
			return &DspSettings_;
		}

	private:

		/**
		* ���ʂ̏�����.
		*/
		void InitCommon();

		/**
		* �I���������Đ����̍X�V����.
		*/
		void UpdateOnMemory();

		/**
		* �X�g���[�~���O�Đ����̍X�V����.
		*/
		void UpdateStreaming();

		/**
		* �Đ�?
		*
		* @param buffer		�o�b�t�@.
		* @param buffersizr	�o�b�t�@�T�C�Y.
		*/
		void Play(char* buffer, UINT buffersize);

		/**
		* �X�g���[�~���O�o�b�t�@�����O�̊J�n.
		*/
		void StartStreamingBuffring();

		/**
		* 3D�T�E���h�̍폜.
		*/
		void Remove3DSound();

	private:

		/** �g�`�f�[�^�N���X. */
		shared_ptr<WaveFile> WaveFile_;
		/** �\�[�X�{�C�X. */
		IXAudio2SourceVoice* SourceVoice_ = nullptr;
		
		/** ���[�v�t���O. */
		bool isLoop_ = false;
		/** �Đ����t���O. */
		bool isPlaying_ = false;

		/** �X�g���[�~���O�Đ��t���O. */
		bool isStreaming_ = false;
		/** �X�g���[�~���O�p�̃o�b�t�@�����O�T�C�Y. */
		UINT StreamingBufferSize_ = 0;
		/** ���݂̃o�b�t�@�����O�̃T�C�Y. */
		UINT CurrentBufferingSize_ = 0;
		/** �ǂݍ��݊J�n�ʒu. */
		UINT ReadStartPos_ = 0;
		/** �����O�o�b�t�@�̃T�C�Y. */
		UINT RingBufferSize_ = 0;

		/** �X�g���[�~���O�X�e�[�^�X. */
		StreamingStateE	StreamingState_ = StreamingStateE::StreamingBuffering;
		
		/** 3D�T�E���h�t���O. */
		bool is3DSound_ = false;
		/** �����̍��W. */
		Vector3 Position_ = Vector3::Zero;
		/** ������1�t���[���O�̍��W. */
		Vector3 LastFramePosition_ = Vector3::Zero;
		/** �ړ����x. */
		Vector3 Velocity_ = Vector3::Zero;

		/** �G�~�b�^�[�̕�͊p. */
		FLOAT32 EmitterAzimuth_[INPUTCHANNELS];
		/** �W���s��. */
		FLOAT32 MatrixCoefficient_[INPUTCHANNELS * OUTPUTCHANNELS];
		/** DSP�Z�b�e�B���O? */
		X3DAUDIO_DSP_SETTINGS DspSettings_;

		/** ��ԍŏ���setPosition�t���O. */
		bool isSetPositionFirst_ = true;

	};

}