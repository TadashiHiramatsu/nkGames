/**
 * @file	_Resources\nkSkinModelDataHandle.h
 *
 * スキンモデルのハンドルクラスの定義.
 */
#pragma once

namespace nkEngine
{
	/** shared_ptr<SkinModelData>を書きやすく短縮. */
	typedef shared_ptr<SkinModelData> SkinModelDataPtrT;

	/**
	 * スキンモデルのハンドルクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class SkinModelDataHandle : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		SkinModelDataHandle()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~SkinModelDataHandle()
		{
		}

		/**
		 * スキンモデルデータの生ポインタを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		SkinModelData* GetBody()
		{
			//クローン作成していたら
			if (SkinModelData_)
			{
				return SkinModelData_.get();
			}
			return OriginSkinModelData_.get();
		}

		/**
		 * 読み込み.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param 		  	skin   	スキン.
		 * @param [in,out]	anim   	アニメーション.
		 * @param 		  	isClone	クローンフラグ.
		 */
		void Load(const SkinModelDataPtrT& skin, Animation* anim, bool isClone);
	
	private:

		/** オリジナルモデルデータ. */
		SkinModelDataPtrT OriginSkinModelData_;
		/**   
		 * モデルデータ   
		 * アニメーションがある場合 
		 * クローン作成しないと同じ動きをしてしまう.
		 */
		unique_ptr<SkinModelData> SkinModelData_;

	};

}// namespace nkEngine