#pragma once

#include"../../../Item/EquipmentItem.h"

class ItemDetailRender
{
public:

	void Start(RectTransform* parent,const Vector3& pos);

	void Update();

	void Render(EquipmentItem* item);

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

	Image IconImage_;
	RectTransform IconTransform_;

	//���O�\��
	Text NameText_;
	RectTransform NameTransform_;

	Text ParameterText_;
	RectTransform ParameterTransform_;

	Text ParamNameText_;
	RectTransform ParamNameTransform_;

};