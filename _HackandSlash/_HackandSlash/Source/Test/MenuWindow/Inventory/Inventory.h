#pragma once

#include"../IMenuWindow.h"
#include"ItemDetailRender.h"

#include"../../Item/InventoryManager.h"

#include"../../Player/PlayerEquipment.h"
#include"../Inventory/EquipmentDetailRender.h"

class Inventory : public IMenuWindow
{
public:

	enum StateE
	{
		Select,	//�I��
		Detail, //�ڍ�
	};

public:

	void Start(RectTransform* rt, float namepos)override;
	void Update()override;
	void Render()override;

	//�E�B���h�E�����Ƃ��̓���
	void Close()override
	{
		ChangeState(StateE::Select);
	}

private:

	//�X�e�[�g��ω�
	void ChangeState(StateE state)
	{
		State_ = state;
	}

	void ChangeItem();

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

	/** �擪����. */
	int LeadIdx[MAX_EQUIPMENT];

	ItemTypeE SelectEquipmentCode[MAX_EQUIPMENT] = 
	{
		ItemTypeE::Arm,
		ItemTypeE::Armor,
		ItemTypeE::Helm,
		ItemTypeE::Shield,
		ItemTypeE::Sword,
		ItemTypeE::Accessory,
		ItemTypeE::Accessory,
		ItemTypeE::Greaves,
	};

	/** �I�𒆂̑���. */
	int SelectEquipment_ = 0;

	/** ������Ԃ̑傫��. */
	float DefaultIconSize_ = 40;

	/**:�I�����̃A�C�R���̑傫��. */
	float SelectIconSize_ = 70;

	Text SelectName_;
	RectTransform SelectNameTransform_;

	//�ڍ�
	Image DetailImage_;
	RectTransform DetailTransform_;

	const static int MAX_DISPLAY = 4;

	int BefSelect_[MAX_EQUIPMENT];
	int NowSelect_[MAX_EQUIPMENT];

	Image DetailSelectImage_;
	RectTransform DetailSelectTransform_;

	/** �A�C�e���\���̘g. */
	ItemDetailRender ItemDetailRender_[MAX_DISPLAY];

	StateE State_;

	/** �����A�C�e���`��. */
	EquipmentDetailRender EquipmentDetailRender_;
	
	PlayerEquipment PlayerEquipment_;

};