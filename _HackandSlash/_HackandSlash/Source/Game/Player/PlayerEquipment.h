#pragma once

#include"../Item/EquipmentItem.h"

/**
* プレイヤーがセットしている装備.
*/
class PlayerEquipment
{
public:

	/**
	* コンストラクタ
	*/
	PlayerEquipment();

	/**
	* デストラクタ
	*/
	~PlayerEquipment()
	{
	}

	/**
	* アイテムを取得
	*
	* @param type	アイテムタイプ.
	*
	* @return アイテム.
	*/
	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return EquipmentItem_[type];
	}

	/**
	* アイテムを設定.
	* 
	* @param item	アイテム.
	*/
	void SetEquipmentItem(EquipmentItem* item)
	{
		EquipmentItem_[item->GetItemType()] = item;
	}

	/**
	* アイテムが設定されているかのフラグを返します.
	*
	* @param type	アイテムタイプ.
	*
	* @return true or false.
	*/
	bool GetIsItemSet(ItemTypeE type) const
	{
		if (EquipmentItem_[type] != nullptr)
		{
			return true;
		}
		return false;
	}

private:

	/** 設定アイテム. */
	EquipmentItem* EquipmentItem_[ItemTypeE::TypeNum];

};