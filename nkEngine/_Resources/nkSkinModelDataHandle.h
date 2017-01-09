/**
 * @file	_Resources\nkSkinModelDataHandle.h
 *
 * スキンモデルのハンドルクラスの定義.
 */
#pragma once

namespace nkEngine
{
	/** shared_ptr<CSkinModelData>を書きやすく短縮. */
	typedef shared_ptr<CSkinModelData> SkinModelDataPtrT;

	/**
	 * スキンモデルのハンドルクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class SkinModelDataHandle
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		SkinModelDataHandle();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~SkinModelDataHandle();

		/**
		 * スキンモデルデータの生ポインタを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		CSkinModelData* GetBody()
		{
			//クローン作成していたら
			if (SkinModelData_)
			{
				return SkinModelData_.get();
			}
			return OriginSkinModelData_.get();
		}

		/**
		 * 初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param 		  	skin   	スキン.
		 * @param [in,out]	anim   	アニメーション.
		 * @param 		  	isClone	クローンフラグ.
		 */
		void Init(const SkinModelDataPtrT& skin, CAnimation* anim, bool isClone);
	
	private:

		/** オリジナルモデルデータ. */
		SkinModelDataPtrT OriginSkinModelData_;
		/**   
		 * モデルデータ   
		 * アニメーションがある場合 
		 * クローン作成しないと同じ動きをしてしまう.
		 */
		unique_ptr<CSkinModelData> SkinModelData_;

	};

}// namespace nkEngine