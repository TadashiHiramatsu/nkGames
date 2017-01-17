/**
 * @file _Sound\nkWaveFile.h
 *
 * �E�F�[�u�t�@�C���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �E�F�[�u�t�@�C���N���X. 
	 * wav�g���q�̃t�@�C�����������߂̃N���X.
	 * 
	 * wave�t�@�C���̓����ǂݍ��݁A�񓯊��ǂݍ��݂��T�|�[�g���܂�.
	 * CWaveFile::Read�͓����ǂݍ��݁ACWaveFile::ReadAsync�͔񓯊��ǂݍ��݂��s���܂�.
	 * ReadAsync���g�p�����ꍇ��CWaveFile::IsReadEnd���g�p���ē������Ƃ��ĉ�����.
	 * 
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	class WaveFile
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		WaveFile()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		~WaveFile()
		{
		}

		/**
		 * wave�t�@�C�����I�[�v��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param fileName �t�@�C����.
		 */
		void Open(const char* fileName);

	private:

		/** �ǂݍ��ݐ�̃o�b�t�@. */
		unique_ptr<char[]> ReadBuffer_ = nullptr;
		/** wave�t�@�C���̃n���h��. */
		HMMIO Hmmio_ = nullptr;
		/** wave�t�@�C���̃t�H�[�}�b�g��`. */
		WAVEFORMATEX* Pwfx_ = nullptr;
		/** wave�t�@�C����ǂݍ��ނƂ��Ɏg�p����. */
		MMCKINFO ChunkRiff_;
		/** wave�t�@�C���̃T�C�Y. */
		DWORD DwSize_ = 0;
		/** �}���`���f�B�ARIFF�`�����N. */
		MMCKINFO Chunk_;
		/** �ǂݍ��ݏI���t���O. */
		volatile bool isReadEnd_;

		/** �񓯊��ǂݍ��ݗp�X���b�h. */
		thread ReadAsyncThread_;
		/** �񓯊��ǂݍ��ݗp�X���b�h���Ăяo����Ă��邩�t���O. */
		bool isInvokeReadAsyncThread_ = false;

		/** �t�@�C���p�X. */
		string FilePath_;
		/** �t�@�C���p�X�̃n�b�V���R�[�h. */
		unsigned int FilePathHash_ = 0;

	};
}