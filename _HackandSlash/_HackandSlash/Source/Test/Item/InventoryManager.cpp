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
		SetItem(ItemDataResource().GetItem(31001 + i));
	}
}

void CInventoryManager::SetItem(IItemData * item)
{
	switch (item->GetItemType())
	{
	case IItemData::ItemTypeE::Sword:
	{
		ItemList[Sword].push_back(item);
	}
	break;
	case IItemData::ItemTypeE::Armor:
	{
		ArmorItemData* armor = dynamic_cast<ArmorItemData*>(item);
		SetArmor(armor);
	}
	break;
	default:
		break;
	}
	
}

IItemData * CInventoryManager::GetItem(ItemTypeE type, int num)
{
	try 
	{
		return ItemList[type].at(num);
	}
	catch(out_of_range& ex)
	{
		return nullptr;
	}
}

void CInventoryManager::SetArmor(ArmorItemData* item)
{
	ItemTypeE type;

	switch (item->GetArmorType())
	{
	case ArmorItemData::ArmorItemTypeE::Helm:
		type = ItemTypeE::Helm;
		break;
	case ArmorItemData::ArmorItemTypeE::Armor:
		type = ItemTypeE::Armor;
		break;
	case ArmorItemData::ArmorItemTypeE::Arm:
		type = ItemTypeE::Arm;
		break;
	case ArmorItemData::ArmorItemTypeE::Greaves:
		type = ItemTypeE::Greaves;
		break;
	default:
		break;
	}

	ItemList[type].push_back(item);

}
