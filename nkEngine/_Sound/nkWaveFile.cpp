/**
 * @file _Sound\nkWaveFile.cpp
 *
 * ウェーブファイルクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkWaveFile.h"

namespace nkEngine
{

	/**
	* waveファイルをオープン.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @param fileName ファイル名.
	*/
	void WaveFile::Open(const char * fileName)
	{
		//ファイルパスを計算.
		char fileP[256];
		sprintf(fileP, "Asset/Sound/%s.wav", fileName);
		FilePath_ = fileP;

		//ハッシュ値を計算
		FileNameHash_ = Hash::MakeHash(fileName);

		Hmmio_ = mmioOpen(const_cast<char*>(FilePath_.c_str()), nullptr, MMIO_ALLOCBUF | MMIO_READ);
		if (Hmmio_ == nullptr)
		{
			//ファイルが開けない.
			return;
		}

		MMCKINFO ckIn;
		PCMWAVEFORMAT pcmWaveFormat;
		memset(&ckIn, 0, sizeof(ckIn));

		//フォーマットにnullを設定.
		WaveFormat_ = nullptr;

		if ((0 != mmioDescend(Hmmio_, &ChunkRiff_, nullptr, 0)))
		{
			//解放.
			Release();
			return;
		}

		if ((ChunkRiff_.ckid != FOURCC_RIFF) || (ChunkRiff_.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		{
			//解放.
			Release();
			return;
		}

		//入力ファイルで 'fmt'チャンクを探します.
		ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (0 != mmioDescend(Hmmio_, &ckIn, &ChunkRiff_, MMIO_FINDCHUNK))
		{
			Release();
			return;
		}

		//チャンクサイズが小さい?.
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

			//コピー.
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
		
		//サイズをコピー.
		DwSize_ = Chunk_.cksize;

	}

	/**
	* 波形データの読み込み.
	*
	* @param pBuffer [out]	波形データを読み込むバッファ.
	* @param size			読み込むデータサイズ.
	* @param currentsize	?.
	*/
	void WaveFile::Read(char * pBuffer, unsigned int size, unsigned int * currentsize)
	{
		MMIOINFO mmioinfoIn;

		if (Hmmio_ == nullptr)
		{
			//ハンドルがnull.
			return;
		}

		if (pBuffer == nullptr)
		{
			//読み込むバッファがnull.
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
			//バッファにバイトをコピーします.
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
	* 波形データの非同期読み込み.
	*
	* @param pBuffer [out]	波形データを読み込むバッファ.
	* @param size			読み込むデータサイズ.
	* @param currentsize	?.
	*/
	void WaveFile::ReadAsync(char * pBuffer, unsigned int size, unsigned int * currentsize)
	{

		//非同期読み込みのスレッドが立っていれば解放.
		if (isInvokeReadAsyncThread_)
		{
			ReadAsyncThread_.join();
			isInvokeReadAsyncThread_ = false;
		}

		//ロードエンドをfalseに設定.
		isReadEnd_ = false;

		//読み込みスレッドを立てる.
		ReadAsyncThread_ = thread([this, pBuffer, size, currentsize]
		{
			this->Read(pBuffer, size, currentsize);
		});

		isInvokeReadAsyncThread_ = true;
	
	}

	/**
	* 波形データのシーク位置をリセット.
	*/
	void WaveFile::ResetFile()
	{

		//読み込み中はリセットさせない.
		while (!isReadEnd_);

		if (Hmmio_ == nullptr)
		{
			//ハンドルがnullなので終了.
			return;
		}

		//データを探す.
		if (-1 == mmioSeek(Hmmio_,ChunkRiff_.dwDataOffset + sizeof(FOURCC),SEEK_SET))
		{
			//見つからなかった.
			return;
		}

		//入力ファイルで 'data'チャンクを検索する.
		Chunk_.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if (0 != mmioDescend(Hmmio_, &Chunk_, &ChunkRiff_, MMIO_FINDCHUNK))
		{
			//なかった.
			return;
		}

	}

	/**
	* 解放.
	*/
	void WaveFile::Release()
	{

		//非同期読み込みのスレッドが立っていれば解放.
		if (isInvokeReadAsyncThread_)
		{
			ReadAsyncThread_.join();
			isInvokeReadAsyncThread_ = false;
		}

		if (Hmmio_ != nullptr)
		{
			//waveファイルのハンドルをクローズ.
			mmioClose(Hmmio_, 0);
			Hmmio_ = nullptr;
		}
		
		//waveフォーマットを削除.
		SAFE_DELETE_ARRAY(WaveFormat_);

	}

}