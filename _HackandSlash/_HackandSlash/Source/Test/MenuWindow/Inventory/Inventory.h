#pragma once

#include"../IMenuWindow.h"

class Inventory : public IMenuWindow
{
public:

	void Start(RectTransform* rt, float namepos)override;
	void Update()override;
	void Render()override;

private:

	/**
	* �A�C�R���̍X�V.
	*/
	void IconUpdate();

private:

	/** �ō�������. */
	const static int MAX_EQUIPMENT = 8;


	//�I��
	Image ChoiceImage_;
	RectTransform ChoiceTransform_;


	//�ʒu�����̂��߂̃g�����X�t�H�[��
	Image MiddleImage_;
	RectTransform MiddleTransform_[2];

	//�A�C�R���o�b�N�摜
	Image IconBackImage_[MAX_EQUIPMENT];
	RectTransform IconBackTransform_[MAX_EQUIPMENT];

	//�A�C�R���摜
	Image IconImage_[MAX_EQUIPMENT];
	RectTransform IconTransform_[MAX_EQUIPMENT];
	
	/** �I�𒆂̑���. */
	int SelectEquipment_ = 0;

	/** ������Ԃ̑傫��. */
	float DefaultIconSize_ = 40;

	/**:�I�����̃A�C�R���̑傫��. */
	float SelectIconSize_ = 60;

	Text SelectName_;
	RectTransform TextTransform_;

	//�ڍ�
	Image DetailImage_;
	RectTransform DetailTransform_;

};