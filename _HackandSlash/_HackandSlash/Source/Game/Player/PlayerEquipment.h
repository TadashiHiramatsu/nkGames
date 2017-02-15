#pragma once

#include"../Item/EquipmentItem.h"

class PlayerEquipment
{

public:

	//�R���X�g���N�^
	PlayerEquipment();

	//�f�X�g���N�^
	~PlayerEquipment()
	{
	}

	//�A�C�e�����擾
	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return EquipmentItem_[type];
	}

	void SetEquipmentItem(EquipmentItem* item)
	{
		EquipmentItem_[item->GetItemType()] = item;
	}

private:

	EquipmentItem* EquipmentItem_[ItemTypeE::TypeNum];

};