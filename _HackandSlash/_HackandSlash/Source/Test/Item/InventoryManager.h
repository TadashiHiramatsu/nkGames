#pragma once

#include"../../Game/Item/IItem.h"

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


public:

	//コンストラクタ
	CInventoryManager()
	{
	}

	//デストラクタ
	~CInventoryManager()
	{
	}

	//初期化
	void Start();

	//アイテムの設定
	void SetItem(IItem* item, ItemTypeE type);

	//アイテムの取得
	IItem* GetItem(ItemTypeE type, int num);

private:

	vector<IItem*> ItemList[ItemTypeE::TypeNum];

};