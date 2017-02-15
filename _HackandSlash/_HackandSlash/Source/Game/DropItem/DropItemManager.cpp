#include"stdafx.h"
#include"DropItemManager.h"

#include"../GameCamera.h"

#include"../Item/InventoryManager.h"

/** 初期化. */
void DropItemManager::Start()
{
	DropItemList_.clear();

	PickUpDistance_ = 0.3;

	AButtonSprite_.Load("Image/AButton.png");
	AButtonSprite_.Start();
	AButtonSprite_.SetTransform(&AButtonTransform_);
	AButtonSprite_.SetCamera(g_MainCamera->GetCamera());
	AButtonTransform_.Scale_ = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

}

/** 更新. */
void DropItemManager::Update()
{
	//ドロップアイテムリストのイテレータを取得
	auto it = DropItemList_.begin();

	while (it != DropItemList_.end())
	{
		//更新
		(*it)->Update();
		it++;
	}

	DropItemList_.sort(DropItem::Comp);

	it = DropItemList_.begin();

	if (it != DropItemList_.end())
	{
		//取得できる距離にアイテムが存在している
		if ((*it)->GettoPlayerLength() <= PickUpDistance_)
		{
			isGetItem_ = true;
			D3DXVECTOR3 pos = (*it)->Transform_.Position_;
			AButtonTransform_.Position_ = pos + D3DXVECTOR3(0, 0.2f, 0);
			AButtonTransform_.BillboardUpdate(g_MainCamera->GetCamera()->GetRotationMatrix());
		}
		else
		{
			isGetItem_ = false;
		}

		if (isGetItem_ && XInput().IsTrigger(ButtonE::ButtonA))
		{
			InventoryManager().SetItem((*it)->GetEquipmentItem());
			DropItemList_.erase(it);
			isGetItem_ = false;
		}
	}
}

/** 描画. */
void DropItemManager::Render()
{
	for (auto it : DropItemList_)
	{
		it->Render();
	}

	if (isGetItem_)
	{
		AButtonSprite_.Render();
	}
}

/** 装備アイテムをドロップアイテムにしてリストに登録する. */
void DropItemManager::SetDropItem(EquipmentItem * item, D3DXVECTOR3 & pos)
{
	
	//ドロップアイテムのポインタを作成
	DropItem* dropitem = new DropItem();
	
	dropitem->Start(item, pos, Player_);

	//リストに設定
	DropItemList_.push_back(dropitem);

}
