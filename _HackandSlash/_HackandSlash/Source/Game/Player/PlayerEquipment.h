#pragma once

#include"../Item/EquipmentItem.h"

class PlayerEquipment
{

public:

	//コンストラクタ
	PlayerEquipment();

	//デストラクタ
	~PlayerEquipment()
	{
	}

	//アイテムを取得
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