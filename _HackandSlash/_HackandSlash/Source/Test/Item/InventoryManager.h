#pragma once

#include"../../Game/Item/IItemData.h"

#include"../../Game/Item/ArmorItemData.h"

/**
* 拾ったアイテムを管理するクラス.
* シーンクラスが管理する.
*/
class CInventoryManager
{

public:

	enum ItemTypeE
	{
		Sword,		//!< 剣
		Shield,		//!< 盾
		Helm,		//!< 頭
		Armor,		//!< 胸
		Arm,		//!< 腕
		Greaves,	//!< 脚
		Accessory,	//!< アクセサリー
		TypeNum,    //!< 数
	};


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
	void SetItem(IItemData* item);

	//アイテムの取得
	IItemData* GetItem(ItemTypeE type, int num);

	int GetItemSize(ItemTypeE type)
	{
		return ItemList[type].size();
	}

private:

	void SetArmor(ArmorItemData* item);

private:

	vector<IItemData*> ItemList[ItemTypeE::TypeNum];

};

static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}