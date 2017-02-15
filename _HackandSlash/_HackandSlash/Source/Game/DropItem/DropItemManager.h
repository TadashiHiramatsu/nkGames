#pragma once

#include"DropItem.h"
#include"../Player/Player.h"

/**
* ドロップアイテムのリストを管理する
*/
class DropItemManager : public IGameObject
{
public:
	
	//コンストラクタ
	DropItemManager()
	{
	}

	//デストラクタ
	~DropItemManager()
	{
	}

	/** 初期化. */
	void Start()override;

	/** 更新. */
	void Update()override;

	/** 描画. */
	void Render()override;

	/** 装備アイテムをドロップアイテムにしてリストに登録する. */
	void SetDropItem(EquipmentItem* item, D3DXVECTOR3& pos);

	/** プレイヤーのポインタを設定. */
	void SetPlayer(Player* player)
	{
		Player_ = player;
	}

	bool GetisGetItem()
	{
		return isGetItem_;
	}

private:

	/** 管理リスト. */
	list<DropItem*> DropItemList_;

	/** アイテムを拾える距離*/
	float PickUpDistance_ = 0;

	/** プレイヤーのポインタ. */
	Player* Player_;

	/** 取得できるアイテムが存在するフラグ*/
	bool isGetItem_ = false;

	/** ボタン. */
	Sprite AButtonSprite_;
	Transform AButtonTransform_;

};

extern DropItemManager* g_DropItemManager;
