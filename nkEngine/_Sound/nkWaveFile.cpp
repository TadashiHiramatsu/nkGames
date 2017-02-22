/**
 * @file _Sound\nkWaveFile.cpp
 *
 * �E�F�[�u�t�@�C���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkWaveFile.h"

namespace nkEngine
{

	/**
	* wave�t�@�C�����I�[�v��.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @param fileName �t�@�C����.
	*/
	void WaveFile::Open(const char * fileName)
	{
		//�t�@�C���p�X���v�Z.
		char fileP[256];
		sprintf(fileP, "Asset/Sound/%s.wav", fileName);
		FilePath_ = fileP;

		//�n�b�V���l���v�Z
		FileNameHash_ = Hash::MakeHash(fileName);

		Hmmio_ = mmioOpen(const_cast<char*>(FilePath_.c_str()), nullptr, MMIO_ALLOCBUF | MMIO_READ);
		if (Hmmio_ == nullptr)
		{
			//�t�@�C�����J���Ȃ�.
			return;
		}

		MMCKINFO ckIn;
		PCMWAVEFORMAT pcmWaveFormat;
		memset(&ckIn, 0, sizeof(ckIn));

		//�t�H�[�}�b�g��null��ݒ�.
		WaveFormat_ = nullptr;

		if ((0 != mmioDescend(Hmmio_, &ChunkRiff_, nullptr, 0)))
		{
			//���.
			Release();
			return;
		}

		if ((ChunkRiff_.ckid != FOURCC_RIFF) || (ChunkRiff_.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		{
			//���.
			Release();
			return;
		}

		//���̓t�@�C���� 'fmt'�`�����N��T���܂�.
		ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (0 != mmioDescend(Hmmio_, &ckIn, &ChunkRiff_, MMIO_FINDCHUNK))
		{
			Release();
			return;
		}

		//�`�����N�T�C�Y��������?.
		if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
		{
			Release();
			return;
		}

		if (mmioRead(Hmmio_, (HPSTR)&pcmWaveFormat,sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
		{
			Release();
			return;
		}

		if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		{
			WaveFormat_ = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];

			memcpy(WaveFormat_, &pcmWaveFormat, sizeof(pcmWaveFormat));
			WaveFormat_->cbSize = 0;

		}
		else
		{
			
			WORD cbExtraBytes = 0L;
		
			if (mmioRead(Hmmio_, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
			{
				Release();
				return;
			}

			WaveFormat_ = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];

			//�R�s�[.
			memcpy(WaveFormat_, &pcmWaveFormat, sizeof(pcmWaveFormat));
			WaveFormat_->cbSize = cbExtraBytes;

			if (mmioRead(Hmmio_, (CHAR*)(((BYTE*)&(WaveFormat_->cbSize)) + sizeof(WORD)),cbExtraBytes) != cbExtraBytes)
			{
				Release();
				return;
			}

		}

		if (0 != mmioAscend(Hmmio_, &ckIn, 0))
		{
			Release();
			return;
		}

		ResetFile();
		
		//�T�C�Y���R�s�[.
		DwSize_ = Chunk_.cksize;

	}

	/**
	* �g�`�f�[�^�̓ǂݍ���.
	*
	* @param pBuffer [out]	�g�`�f�[�^��ǂݍ��ރo�b�t�@.
	* @param size			�ǂݍ��ރf�[�^�T�C�Y.
	* @param currentsize	?.
	*/
	void WaveFile::Read(char * pBuffer, unsigned int size, unsigned int * currentsize)
	{
		MMIOINFO mmioinfoIn;

		if (Hmmio_ == nullptr)
		{
			//�n���h����null.
			return;
		}

		if (pBuffer == nullptr)
		{
			//�ǂݍ��ރo�b�t�@��null.
			return;
		}

		if (0 != mmioGetInfo(Hmmio_, &mmioinfoIn, 0))
		{
			return;
		}

		UINT cbDataIn = size;
		if (cbDataIn > Chunk_.cksize)
		{
			cbDataIn = Chunk_.cksize;
		}

		*currentsize = cbDataIn;
		Chunk_.cksize -= cbDataIn;

		for (DWORD cT = 0; cT < cbDataIn; cT++)
		{
			//�o�b�t�@�Ƀo�C�g���R�s�[���܂�.
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				if (0 != mmioAdvance(Hmmio_, &mmioinfoIn, MMIO_READ))
				{
					return;
				}

				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				{
					return;
				}

			}

			*((BYTE*)pBuffer + cT) = *((BYTE*)mmioinfoIn.pchNext);
			mmioinfoIn.pchNext++;

		}

		isReadEnd_ = true;
		return;

	}

	/**
	* �g�`�f�[�^�̔񓯊��ǂݍ���.
	*
	* @param pBuffer [out]	�g�`�f�[�^��ǂݍ��ރo�b�t�@.
	* @param size			�ǂݍ��ރf�[�^�T�C�Y.
	* @param currentsize	?.
	*/
	void WaveFile::ReadAsync(char * pBuffer, unsigned int size, unsigned int * currentsize)
	{

		//�񓯊��ǂݍ��݂̃X���b�h�������Ă���Ή��.
		if (isInvokeReadAsyncThread_)
		{
			ReadAsyncThread_.join();
			isInvokeReadAsyncThread_ = false;
		}

		//���[�h�G���h��false�ɐݒ�.
		isReadEnd_ = false;

		//�ǂݍ��݃X���b�h�𗧂Ă�.
		ReadAsyncThread_ = thread([this, pBuffer, size, currentsize]
		{
			this->Read(pBuffer, size, currentsize);
		});

		isInvokeReadAsyncThread_ = true;
	
	}

	/**
	* �g�`�f�[�^�̃V�[�N�ʒu�����Z�b�g.
	*/
	void WaveFile::ResetFile()
	{

		//�ǂݍ��ݒ��̓��Z�b�g�����Ȃ�.
		while (!isReadEnd_);

		if (Hmmio_ == nullptr)
		{
			//�n���h����null�Ȃ̂ŏI��.
			return;
		}

		//�f�[�^��T��.
		if (-1 == mmioSeek(Hmmio_,ChunkRiff_.dwDataOffset + sizeof(FOURCC),SEEK_SET))
		{
			//������Ȃ�����.
			return;
		}

		//���̓t�@�C���� 'data'�`�����N����������.
		Chunk_.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if (0 != mmioDescend(Hmmio_, &Chunk_, &ChunkRiff_, MMIO_FINDCHUNK))
		{
			//�Ȃ�����.
			return;
		}

	}

	/**
	* ���.
	*/
	void WaveFile::Release()
	{

		//�񓯊��ǂݍ��݂̃X���b�h�������Ă���Ή��.
		if (isInvokeReadAsyncThread_)
		{
			ReadAsyncThread_.join();
			isInvokeReadAsyncThread_ = false;
		}

		if (Hmmio_ != nullptr)
		{
			//wave�t�@�C���̃n���h�����N���[�Y.
			mmioClose(Hmmio_, 0);
			Hmmio_ = nullptr;
		}
		
		//wave�t�H�[�}�b�g���폜.
		SAFE_DELETE_ARRAY(WaveFormat_);

	}

}