#pragma once

#include"../../Item/EquipmentItem.h"

class EquipmentDetailRender
{
public:

	//������
	void Start(RectTransform* parent);

	//�X�V
	void Update();

	//�`��
	void Render(EquipmentItem* item);

private:

	/** �o�b�N�摜. */
	Image BackImage_;
	RectTransform BackTransform_;

	Text ItemNameText_;
	RectTransform ItemNameTransform_;

};