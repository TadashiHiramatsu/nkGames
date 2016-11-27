#include"nkEngine/nkstdafx.h"
#include"nkSkinModelDataHandle.h"

namespace nkEngine
{
	void CSkinModelDataHandle::Init(const shared_ptr<CSkinModelData>& _Skin, CAnimation * _Anim, bool _isClone)
	{
		OriginSkinModelData = _Skin;
		if (_isClone)
		{
			//クローンを作成
			SkinModelData.reset(new CSkinModelData);
			SkinModelData->CloneModelData(*_Skin, _Anim);
		}
	}

}