#pragma once

#include"EquipmentItem.h"
#include"ItemData\ArmorItemData.h"

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

	/**
	* インスタンスを取得.
	*/
	static CInventoryManager& GetInstance()
	{
		static CInventoryManager instance;
		return instance;
	}

	/**
	* 初期化.
	*/
	void Start();

	/**
	* アイテムの設定.
	*/
	void SetItem(EquipmentItem* item);

	/**
	* アイテムの取得.
	*/
	EquipmentItem* GetItem(ItemTypeE type, int num);

	/**
	* アイテム所持数を取得.
	*/
	int GetItemSize(ItemTypeE type)
	{
		return ItemList_[type].size();
	}

	/**
	* アイテムを変更.
	*/
	EquipmentItem* ChangeItem(ItemTypeE type, EquipmentItem* item, int num);

private:

	/**
	* 読み取り.
	*/
	void Continue();

public:

	/**
	* 書き込み.
	*/
	void Save();

private:

	/** アイテムリスト. */
	vector<EquipmentItem*> ItemList_[ItemTypeE::TypeNum];

};

/**
* インベントリマネージャの取得.
*/
static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}