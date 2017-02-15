#pragma once

#include"../../../Item/EquipmentItem.h"

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

	/** �t���[���摜. */
	Image FrameImage_;
	RectTransform FrameTransform_;

	/** �o�b�N�摜. */
	Image BackImage_;
	RectTransform BackTransform_;

	Image IconBackImage_;
	RectTransform IconBackTransform_;

	Image IconImage_;
	RectTransform IconTransform_;


	Text ItemNameText_;
	RectTransform ItemNameTransform_;

	Text ParameterText_;
	RectTransform ParameterTransform_;

	Text ParamNameText_;
	RectTransform ParamNameTransform_;

};