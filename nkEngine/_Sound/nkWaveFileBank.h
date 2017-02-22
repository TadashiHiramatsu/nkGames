#pragma once

namespace nkEngine
{
	class WaveFile;

	/** WaveFile�N���X�̃V�F�A�[�h�|�C���^�̃V�m�j��. */
	typedef shared_ptr<WaveFile> WaveFilePtrT;

	/** WaveFile�N���X���n�b�V���Ǘ����Ă���}�b�v�̃V�m�j��. */
	typedef map<UINT, WaveFilePtrT> WaveFileMap;

	/**
	* �g�`�f�[�^�o���N.
	* 
	* ��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^���邱�Ƃ��o���܂��B
	* �o�^���ꂽ�g�`�f�[�^�͍ēǂݍ��݂��s���K�v���Ȃ��A�o���N����ė��p���邱�Ƃ��o���܂��B
	*/
	class WaveFileBank
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		WaveFileBank()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~WaveFileBank()
		{
			ReleaseAll();
		}

		/**
		* �g�`�f�[�^��o�^.
		* 
		* @param groupID	�O���[�vID.
		* @param wavefile	�g�`�f�[�^.
		*/
		void SetWaveFile(int groupID, WaveFilePtrT wavefile);

		/**
		* �����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������.
		*
		* @param groupID	�O���[�vID.
		* @param filepath	�t�@�C����.
		*/
		WaveFilePtrT FindWaveFile(int groupID, const char* filename);

		/**
		* �O���[�v�P�ʂŉ��.
		*
		* @param groupID	�O���[�vID.
		*/
		void Release(int groupID);

		/*
		* ���ׂĉ��.
		*/
		void ReleaseAll()
		{
			for (int i = 0; i < MAX_GROUP; i++)
			{
				Release(i);
			}
		}

	private:

		/** �O���[�v�̍ő吔. */
		static const int MAX_GROUP = 256;
		/** wave�t�@�C���̃��X�g. */
		WaveFileMap WaveFileMap_[MAX_GROUP];

	};

}