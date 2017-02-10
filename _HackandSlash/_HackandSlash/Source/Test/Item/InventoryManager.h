#pragma once

#include"EquipmentItem.h"
#include"ItemType.h"
#include"../../Game/Item/ArmorItemData.h"

/**
* 拾ったアイテムを管理するクラス.
* シーンクラスが管理する.
*/
class CInventoryManager
{

private:

	//コンストラクタ
	CInventoryManager()
	{
	}

	//デストラクタ
	~CInventoryManager()
	{
	}

public:

	static CInventoryManager& GetInstance()
	{
		static CInventoryManager instance;
		return instance;
	}

	//初期化
	void Start();

	//アイテムの設定
	void SetItem(EquipmentItem* item);

	//アイテムの取得
	EquipmentItem* GetItem(ItemTypeE type, int num);

	int GetItemSize(ItemTypeE type)
	{
		return ItemList[type].size();
	}

	EquipmentItem* ChangeItem(ItemTypeE type,EquipmentItem* item, int num);

private:

	vector<EquipmentItem*> ItemList[ItemTypeE::TypeNum];

};

static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}