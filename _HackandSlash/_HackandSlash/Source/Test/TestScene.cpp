#include"stdafx.h"
#include"TestScene.h"

#include"MenuWindow\MenuSystem.h"

#include"Item\InventoryManager.h"

#include"../Game/Item/ItemDataResource.h"

void TestScene::Start()
{
	NewGO<MenuSystem>();

	ItemDataResource().Load();

	InventoryManager().Start();

}
