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

	private:

		/** 読み込み先のバッファ. */
		unique_ptr<char[]> ReadBuffer_ = nullptr;
		/** waveファイルのハンドル. */
		HMMIO Hmmio_ = nullptr;
		/** waveファイルのフォーマット定義. */
		WAVEFORMATEX* Pwfx_ = nullptr;
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
		/** ファイルパスのハッシュコード. */
		unsigned int FilePathHash_ = 0;

	};
}