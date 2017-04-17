#include"stdafx.h"
#include"InventoryManager.h"

#include"../../Game/Item/ItemDataResource.h"

#include"../../Common/SaveData/SaveData.h"

/**
* ������.
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
* �A�C�e����ݒ�.
*/
void CInventoryManager::SetItem(EquipmentItem* item)
{
	ItemList_[item->GetItemType()].push_back(item);
}

/**
* �A�C�e�����擾.
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
* �A�C�e����ύX.
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
* �ǂݍ���.
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
* ��������.
*/
void CInventoryManager::Save()
{
	//�A�C�e�����X�g.
	picojson::array itemlist;

	for (int type = 0; type < ItemTypeE::TypeNum; type++)
	{
		for (int num = 0; num < ItemList_[type].size(); num++)
		{
			//��ID.
			int id = ItemList_[type][num]->GetID();

			//�A�C�e��.
			picojson::object item;

			item["ID"] = (picojson::value)(double)id;

			itemlist.push_back((picojson::value)item);
		}
	}

	//�A�C�e���f�[�^.
	picojson::object itemdata;
	itemdata["ItemList"] = (picojson::value)itemlist;

	//�f�[�^��������.
	SaveData().SetDataObject("ItemData", itemdata);

}