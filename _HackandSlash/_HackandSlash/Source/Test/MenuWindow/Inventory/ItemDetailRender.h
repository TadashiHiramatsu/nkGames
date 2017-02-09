#pragma once

#include"../../../Game/Item/IItemData.h"

class ItemDetailRender
{
public:

	void Start(RectTransform* parent, D3DXVECTOR3& pos);

	void Update();

	void Render(IItemData* item);

	RectTransform* GetTransform()
	{
		return &BackTransform_;
	}

private:

	/** バック画像. */
	Image BackImage_;
	RectTransform BackTransform_;

	Image IconBackImage_;
	RectTransform IconBackTransform_;

	//名前表示
	Text NameText_;
	RectTransform NameTransform_;

};