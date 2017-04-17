/**
* ���j���[�E�B���h�E�̃C���x���g���E�B���h�E�N���X�̒�`.
*/
#pragma once

#include"../IMenuWindow.h"
#include"ItemDetailRender.h"

#include"../../../Item/InventoryManager.h"

#include"../../../Player/PlayerEquipment.h"

#include"../Inventory/EquipmentDetailRender.h"

/**
* ���j���[�E�B���h�E�̃C���x���g���E�B���h�E�N���X.
*/
class InventoryWindow : public IMenuWindow
{
public:

	/** ��ԃR�[�h. */
	enum class StateE
	{
		Select,	//!< �I��.
		Detail, //!< �ڍ�.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	InventoryWindow()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~InventoryWindow()
	{
	}

	/**
	* ������.
	*/
	void Start(RectTransform* rt, float namepos)override;
	
	/**
	* �X�V.
	*/
	void Update()override;
	
	/**
	* �`��.
	*/
	void Render()override;

	/**
	* �E�B���h�E�����Ƃ��̓���.
	*/
	void Close()override
	{
		ChangeState(StateE::Select);
	}

private:

	/**
	* �X�e�[�g��ω�.
	*/
	void ChangeState(StateE state)
	{
		State_ = state;
	}

	/**
	* �A�C�e��������.
	*/
	void ChangeItem();

private:

	/** �ō�������. */
	const static int MAX_EQUIPMENT = 8;

	/** �I���摜. */
	Image ChoiceImage_;
	/** �I���g�����X�t�H�[��. */
	RectTransform ChoiceTransform_;

	/** ���S�摜. */
	Image MiddleImage_;
	/** �ʒu�����̂��߂̃g�����X�t�H�[��. */
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
		ItemTypeE::Weapon,
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

	/** �A�C�e���\����. */
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
	
	/** �����i�e�L�X�g. */
	Text ShojiText_;
	RectTransform ShojiTransform_;

	/** �����i�e�L�X�g. */
	Text SoubiText_;
	RectTransform SoubiTransform_;

};