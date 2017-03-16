/**
* �T�E���h�G���W���N���X�̒�`.
*/
#pragma once

#include"nkWaveFileBank.h"
#include"../_Math/nkVector.h"

#define INPUTCHANNELS 2		//!< number of source channels
#define OUTPUTCHANNELS 8	//!< �ő�o�̓`�����l����.

namespace nkEngine
{
	class WaveFile;
	class SoundSource;

	/**
	* �T�E���h�G���W���N���X.
	*/
	class CSoundEngine : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		CSoundEngine()
		{
			memset(X3DAudioHandle_, 0, sizeof(X3DAudioHandle_));
		}

		/**
		* �f�X�g���N�^.
		*/
		~CSoundEngine()
		{
			Release();
		}

		/**
		* ������.
		*/
		void Init();

		/**
		* �X�V.
		*/
		void Update();

		/**
		* ���.
		*/
		void Release();

		/**
		* 3D�T�E���h�\�[�X��ǉ�.
		*
		* @param s	�T�E���h�\�[�X.
		*/
		void Add3DSoundSource(SoundSource* s)
		{
			SoundSource3DList_.push_back(s);
		}

		/**
		* 3D�T�E���h�\�[�X�̍폜.
		*/
		void Remove3DSoundSource(SoundSource* s)
		{
			auto& it = find(SoundSource3DList_.begin(), SoundSource3DList_.end(), s);
			if (it != SoundSource3DList_.end())
			{
				SoundSource3DList_.erase(it);
			}
		}

		/**
		* �T�E���h���X�i�[�̍��W��ݒ�.
		*
		* @param pos	�ʒu�x�N�g��.
		*/
		void SetListenerPosition(const Vector3& pos)
		{
			ListenerPosition_ = pos;
		}

		/**
		* �T�E���h���X�i�[�̑O������ݒ�.
		*
		* @param front	�O�����x�N�g��.
		*/
		void SetListenerFront(const Vector3& front)
		{
			front.CopyTo(Listener_.OrientFront);
		}

		/**
		* �T�E���h���X�i�[�̏������ݒ�.
		*
		* @param up		������x�N�g��.
		*/
		void SetListenerUp(const Vector3& up)
		{
			up.CopyTo(Listener_.OrientTop);
		}

		/**
		* XAudio2�̃\�[�X�{�C�X���쐬.
		*
		* @param wavefile	�g�`�f�[�^.
		* @param is3Dsound	3D�T�E���h�t���O.
		*/
		IXAudio2SourceVoice* CreateSourceVoice(WaveFile* wavefile, bool is3Dsound);

		/**
		* �}�X�^�[�{�C�X���擾.
		*/
		IXAudio2MasteringVoice* GetMasteringVoice()
		{
			return MasteringVoice_;
		}

		/**
		* �T�u�~�b�N�X�{�C�X�̎擾.
		*/
		IXAudio2SubmixVoice* GetSubmixVoice()
		{
			return SubmixVoice_;
		}

		/**
		* �o�̓`�����l�������擾.
		*/
		int GetChannelNum() const
		{
			return ChannelNum_;
		}

		/**
		* �g�`�f�[�^�o���N���擾.
		*/
		WaveFileBank& GetWaveFileBank()
		{
			return WaveFileBank_;
		}


	private:

		/** �������t���O. */
		bool isInit = false;

		/** XAudio2�̃C���^�[�t�F�C�X. */
		IXAudio2* XAudio2_ = nullptr;
		/** �}�X�^�[�{�C�X. */
		IXAudio2MasteringVoice* MasteringVoice_ = nullptr;
		/** 3D�I�[�f�B�I�̃n���h��. */
		X3DAUDIO_HANDLE X3DAudioHandle_;
		/** ���o�[�u�G�t�F�N�g. */
		IUnknown* ReverbEffect_ = nullptr;
		/** �T�u�~�b�N�X�{�C�X. */
		IXAudio2SubmixVoice* SubmixVoice_ = nullptr;
		/** �I�[�f�B�I�`�����l���}�X�N. */
		DWORD ChannnelMask_;
		/** �`�����l����. */
		DWORD ChannelNum_;
		
		/** �T�E���h���X�i�[. */
		X3DAUDIO_LISTENER Listener_;
		/** ���X�i�[�̈ʒu. */
		Vector3 ListenerPosition_ = Vector3::Zero;
		/** ���X�i�[�̊p�x. */
		float ListenerAngle_ = 0;
		/** ���X�i�[�R�[���t���O. */
		bool isListenerCone_ = false;
		/** �~���a�t���O. */
		bool isInnerRadius_ = false;
		
		/** �ቹ�����t���O?. */
		bool isRedirectToLFE_ = false;
		
		/** 3D�T�E���h�\�[�X���X�g. */
		list<SoundSource*> SoundSource3DList_;
		
		/** �G�~�b�^�[�R�[��. */
		X3DAUDIO_CONE EmitterCone_;

		/** �g�`�f�[�^�o���N. */
		WaveFileBank WaveFileBank_;
	
	};

}