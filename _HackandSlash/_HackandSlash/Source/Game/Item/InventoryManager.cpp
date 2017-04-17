#include"stdafx.h"
#include"InventoryManager.h"

#include"../../Game/Item/ItemDataResource.h"

#include"../../Common/SaveData/SaveData.h"

/**
* 初期化.
*/
void CInventoryManager::Start()
{
	for (int i = 0; i < ItemTypeE::TypeNum; i++)
	{
		ItemList_[i].clear();
	}

	Continue();
}

/**
* アイテムを設定.
*/
void CInventoryManager::SetItem(EquipmentItem* item)
{
	ItemList_[item->GetItemType()].push_back(item);
}

/**
* アイテムを取得.
*/
EquipmentItem* CInventoryManager::GetItem(ItemTypeE type, int num)
{
	try
	{
		return ItemList_[type].at(num);
	}
	catch(out_of_range& ex)
	{
		return nullptr;
	}
}

/**
* アイテムを変更.
*/
EquipmentItem* CInventoryManager::ChangeItem(ItemTypeE type, EquipmentItem* item, int num)
{
	EquipmentItem* retitem;

	retitem = GetItem(type,num);
	
	if (item != nullptr)
	{
		ItemList_[type][num] = item;
	}
	else
	{
		ItemList_[type].erase(ItemList_[type].begin() + num);
	}

	return retitem;
}

/**
* 読み込み.
*/
void CInventoryManager::Continue()
{
	if (SaveData().IsContinue())
	{
		picojson::object itemdata = SaveData().GetDataObject("ItemData");

		picojson::array itemlist = itemdata["ItemList"].get<picojson::array>();

		for (int i = 0; i < itemlist.size(); i++)
		{
			picojson::object item = itemlist[i].get<picojson::object>();
			int id = item["ID"].get<double>();

			EquipmentItem* eitem = new EquipmentItem(ItemDataResource().GetItemData(id));
			SetItem(eitem);
		}
	}
}

/**
* 書き込み.
*/
void CInventoryManager::Save()
{
	//アイテムリスト.
	picojson::array itemlist;

	for (int type = 0; type < ItemTypeE::TypeNum; type++)
	{
		for (int num = 0; num < ItemList_[type].size(); num++)
		{
			//個別ID.
			int id = ItemList_[type][num]->GetID();

			//アイテム.
			picojson::object item;

			item["ID"] = (picojson::value)(double)id;

			itemlist.push_back((picojson::value)item);
		}
	}

	//アイテムデータ.
	picojson::object itemdata;
	itemdata["ItemList"] = (picojson::value)itemlist;

	//データ書き込み.
	SaveData().SetDataObject("ItemData", itemdata);

}