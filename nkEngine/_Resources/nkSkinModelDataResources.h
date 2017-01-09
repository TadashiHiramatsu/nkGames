/**
 * @file	_Resources\nkSkinModelDataResources.h
 *
 * スキンモデルのリソースクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * スキンモデルのリソース管理クラス.
	 * シングルトンクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CSkinModelDataResources
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CSkinModelDataResources();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CSkinModelDataResources();
	
	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CSkinModelDataResources& GetInstance()
		{
			static CSkinModelDataResources instance;
			return instance;
		}

		/**
		 * 読み取り.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	skinModelDataHandle	スキンモデルデータハンドル.
		 * @param 		  	filePath		   	ファイルパス.
		 * @param [in,out]	anim			   	アニメーション.
		 * @param 		  	isInstancing	   	(Optional) インスタンシングフラグ.
		 * @param 		  	numInstancing	   	(Optional) インスタンス数.
		 */
		void Load(
			SkinModelDataHandle& skinModelDataHandle, 
			const char* filePath, 
			CAnimation* anim,
			bool isInstancing = false,
			int numInstancing = 0
		);

	private:

		/** Defines an alias representing the skin model data map. */
		typedef map<int, SkinModelDataPtrT> SkinModelDataMapT;
		/** インスタンシングしないが複数回使うモデルを保存. */
		SkinModelDataMapT SkinModelDataMap_;
		/** インスタンシングモデルを保存. */
		list<SkinModelDataPtrT> InstancingList_;

	};

	/**
	 * スキンモデルのリソース管理クラスの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to the CSkinModelDataResources.
	 */
	static CSkinModelDataResources& SMDResources()
	{
		return CSkinModelDataResources::GetInstance();
	}

}// namespace nkEngine