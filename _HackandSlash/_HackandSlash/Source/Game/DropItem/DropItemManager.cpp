#include"stdafx.h"
#include"DropItemManager.h"

#include"../GameCamera.h"

#include"../Item/InventoryManager.h"
#include"../Item/ItemDataResource.h"

/** 初期化. */
void DropItemManager::Start()
{
	DropItemList_.clear();

	PickUpDistance_ = 2.0f;

	AButtonSprite_.Load("Image/AButton.png");
	AButtonSprite_.Start();
	AButtonSprite_.SetTransform(&AButtonTransform_);
	AButtonSprite_.SetCamera(g_MainCamera->GetCamera());
	AButtonTransform_.Scale_ = Vector3(0.1f, 0.1f, 1.0f);

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
			Vector3 pos = (*it)->Transform_.Position_;
			AButtonTransform_.Position_.Add(pos, Vector3(0, 0.5f, 0));
			AButtonTransform_.BillboardUpdate(g_MainCamera->GetCamera()->GetRotationMatrix());
		}
		else
		{
			isGetItem_ = false;
		}

		if (isGetItem_ && XInput().IsTrigger(ButtonE::A))
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

void DropItemManager::SetDropItem(int level,const Vector3 & pos)
{
	//この敵が落とすアイテム
	vector<DataS*> ItemList;

	//実際のドロップ値?
	int probability = 0;

	//存在するアイテム.
	auto& ItemMap = ItemDataResource().GetItemMap();
	for (auto it : ItemMap)
	{
		if (it.second->GetMinLevel() <= level && level <= it.second->GetMaxLevel())
		{
			DataS* data = new DataS();

			//アイテムデータを設定.
			data->ItemData_ = it.second;

			//ドロップ率を加算
			probability += it.second->GetProbability();

			//ドロップ率を設定
			data->Probability_ = probability;


			ItemList.push_back(data);
		}
	}

	int p = Random().Range(0, max(999999, probability));

	EquipmentItem* item = nullptr;

	for(auto it : ItemList)
	{
		if (p < it->Probability_)
		{
			item = new EquipmentItem(it->ItemData_);
			break;
		}
	}

	if (item != nullptr)
	{

		//ドロップアイテムのポインタを作成
		DropItem* dropitem = new DropItem();
		dropitem->Start(item, pos, Player_);

		//リストに設定
		DropItemList_.push_back(dropitem);
	}

	ItemList.clear();
}
