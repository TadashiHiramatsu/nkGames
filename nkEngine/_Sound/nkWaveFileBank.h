#pragma once

namespace nkEngine
{
	class WaveFile;

	/** WaveFileクラスのシェアードポインタのシノニム. */
	typedef shared_ptr<WaveFile> WaveFilePtrT;

	/** WaveFileクラスをハッシュ管理しているマップのシノニム. */
	typedef map<UINT, WaveFilePtrT> WaveFileMap;

	/**
	* 波形データバンク.
	* 
	* 一度ロードされた波形データをバンクに登録することが出来ます。
	* 登録された波形データは再読み込みを行う必要がなく、バンクから再利用することが出来ます。
	*/
	class WaveFileBank
	{
	public:

		/**
		* コンストラクタ.
		*/
		WaveFileBank()
		{
		}

		/**
		* デストラクタ.
		*/
		~WaveFileBank()
		{
			ReleaseAll();
		}

		/**
		* 波形データを登録.
		* 
		* @param groupID	グループID.
		* @param wavefile	波形データ.
		*/
		void SetWaveFile(int groupID, WaveFilePtrT wavefile);

		/**
		* 引数で指定したファイルパスの波形データがバンクに登録されているか検索する.
		*
		* @param groupID	グループID.
		* @param filepath	ファイル名.
		*/
		WaveFilePtrT FindWaveFile(int groupID, const char* filename);

		/**
		* グループ単位で解放.
		*
		* @param groupID	グループID.
		*/
		void Release(int groupID);

		/*
		* すべて解放.
		*/
		void ReleaseAll()
		{
			for (int i = 0; i < MAX_GROUP; i++)
			{
				Release(i);
			}
		}

	private:

		/** グループの最大数. */
		static const int MAX_GROUP = 256;
		/** waveファイルのリスト. */
		WaveFileMap WaveFileMap_[MAX_GROUP];

	};

}