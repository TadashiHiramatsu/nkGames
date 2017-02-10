#include"stdafx.h"
#include"InventoryManager.h"

#include"../../Game/Item/ItemDataResource.h"
#include"../../Game/Item/ArmorItemData.h"

void CInventoryManager::Start()
{
	for (int i = 0; i < ItemTypeE::TypeNum; i++)
	{
		ItemList[i].clear();
	}

	for (int i = 0; i < 6; i++)
	{
		EquipmentItem* item = new EquipmentItem(ItemDataResource().GetItem(3001 + i));
		SetItem(item);
	}

	for (int i = 0; i < 3; i++)
	{
		EquipmentItem* item = new EquipmentItem(ItemDataResource().GetItem(4001));
		SetItem(item);
	}

}

void CInventoryManager::SetItem(EquipmentItem* item)
{
	ItemList[item->GetItemType()].push_back(item);
}

EquipmentItem* CInventoryManager::GetItem(ItemTypeE type, int num)
{
	try
	{
		return ItemList[type].at(num);;
	}
	catch(out_of_range& ex)
	{
		return nullptr;
	}
}

EquipmentItem * CInventoryManager::ChangeItem(ItemTypeE type,EquipmentItem* item, int num)
{
	EquipmentItem* retitem = nullptr;

	retitem = GetItem(type, num);
	
	if (item != nullptr)
	{
		ItemList[type][num] = item;
	}
	else
	{
		ItemList[type].erase(ItemList[type].begin() + num);
	}

	return retitem;
}