/**
 * @file	_Resources\nkSkinModelDataHandle.cpp
 *
 * スキンモデルのハンドルクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSkinModelDataHandle.h"

namespace nkEngine
{

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
	void SkinModelDataHandle::Load(const SkinModelDataPtrT& skin, Animation* anim, bool isClone)
	{
		OriginSkinModelData_ = skin;
		if (isClone)
		{
			//クローンを作成
			SkinModelData_.reset(new SkinModelData);
			SkinModelData_->CloneModelData(*skin, anim);
		}
	}

}
