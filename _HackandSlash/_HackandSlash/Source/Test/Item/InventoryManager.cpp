#include"stdafx.h"
#include"InventoryManager.h"

void CInventoryManager::Start()
{
	for (int i = 0; i < ItemTypeE::TypeNum; i++)
	{
		ItemList[i].clear();
	}

}

void CInventoryManager::SetItem(IItem * item, ItemTypeE type)
{
	ItemList[type].push_back(item);
}

IItem * CInventoryManager::GetItem(ItemTypeE type, int num)
{
	return 	ItemList[type].at(num);
}
