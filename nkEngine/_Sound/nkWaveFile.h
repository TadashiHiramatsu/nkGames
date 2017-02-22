/**
 * @file _Sound\nkWaveFile.h
 *
 * ウェーブファイルクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ウェーブファイルクラス. 
	 * wav拡張子のファイルを扱うためのクラス.
	 * 
	 * waveファイルの同期読み込み、非同期読み込みをサポートします.
	 * CWaveFile::Readは同期読み込み、CWaveFile::ReadAsyncは非同期読み込みが行われます.
	 * ReadAsyncを使用した場合はCWaveFile::IsReadEndを使用して同期をとって下さい.
	 * 
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	class WaveFile
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		WaveFile()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		~WaveFile()
		{
			Release();
		}

		/**
		 * waveファイルをオープン.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param fileName ファイル名.
		 */
		void Open(const char* fileName);

		/**
		* 波形データの読み込み.
		*
		* @param pBuffer [out]	波形データを読み込むバッファ.
		* @param size			読み込むデータサイズ.
		* @param currentsize	?.
		*/
		void Read(char* pBuffer, unsigned int size, unsigned int* currentsize);

		/**
		* 波形データの非同期読み込み.
		*
		* @param pBuffer [out]	波形データを読み込むバッファ.
		* @param size			読み込むデータサイズ.
		* @param currentsize	?.
		*/
		void ReadAsync(char* pBuffer, unsigned int size, unsigned int* currentsize);

		/**
		* 読み込み終了判定の取得.
		*/
		bool IsReadEnd() const
		{
			return isReadEnd_;
		}

		/**
		* 波形データのシーク位置をリセット.
		*/
		void ResetFile();

		/**
		* 解放.
		*/
		void Release();

		/**
		* ファイルサイズを取得.
		*/
		DWORD GetSize() const
		{
			return DwSize_;
		}

		/**
		* ファイルフォーマットを取得.
		*/
		WAVEFORMATEX* GetFormat()const
		{
			return WaveFormat_;
		}

		/**
		* ファイル名のハッシュ値を取得.
		*/
		UINT GetFileNameHash() const
		{
			return FileNameHash_;
		}

		/**
		* 読み込み先のバッファを確保.
		*/
		void AllocReadBuffer(int size)
		{
			ReadBuffer_.reset(new char[size]);
		}

		/**
		* 読み込み先のバッファを取得.
		*/
		char* GetReadBuffer()
		{
			return ReadBuffer_.get();
		}

	private:

		/** 読み込み先のバッファ. */
		unique_ptr<char[]> ReadBuffer_ = nullptr;
		/** waveファイルのハンドル. */
		HMMIO Hmmio_ = nullptr;
		/** waveファイルのフォーマット定義. */
		WAVEFORMATEX* WaveFormat_ = nullptr;
		/** waveファイルを読み込むときに使用する. */
		MMCKINFO ChunkRiff_;
		/** waveファイルのサイズ. */
		DWORD DwSize_ = 0;
		/** マルチメディアRIFFチャンク. */
		MMCKINFO Chunk_;
		/** 読み込み終了フラグ. */
		volatile bool isReadEnd_;

		/** 非同期読み込み用スレッド. */
		thread ReadAsyncThread_;
		/** 非同期読み込み用スレッドが呼び出されているかフラグ. */
		bool isInvokeReadAsyncThread_ = false;

		/** ファイルパス. */
		string FilePath_;
		/** ファイル名のハッシュコード. */
		UINT FileNameHash_ = 0;

	};
}