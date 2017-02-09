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

	/** �o�b�N�摜. */
	Image BackImage_;
	RectTransform BackTransform_;

	Image IconBackImage_;
	RectTransform IconBackTransform_;

	//���O�\��
	Text NameText_;
	RectTransform NameTransform_;

};