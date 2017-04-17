#pragma once

#include"DropItem.h"
#include"../Player/Player.h"

/**
* ドロップアイテムのリストを管理する
*/
class DropItemManager : public IGameObject
{
public:

	struct DataS
	{
		/** アイテムデータ. */
		IItemData* ItemData_;
		/** ドロップ率. */
		int Probability_;
	};

public:
	
	//コンストラクタ
	DropItemManager()
	{
	}

	//デストラクタ
	~DropItemManager()
	{
	}

	/** 
	* 初期化. 
	*/
	void Start()override;

	/**
	* 更新. 
	*/
	void Update()override;

	/** 
	* 描画. 
	*/
	void Render()override;

	/** 
	* 装備アイテムをドロップアイテムにしてリストに登録する. 
	*
	* @param level	敵のレベル.
	* @param pos	ドロップする座標.
	**/
	void SetDropItem(int level, const Vector3& pos);

	/** プレイヤーのポインタを設定. */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

	bool GetisGetItem() const
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
