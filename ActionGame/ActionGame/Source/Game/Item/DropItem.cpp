#include"stdafx.h"
#include"DropItem.h"

#include"../GameScene.h"
#include"..\GameCamera.h"
#include"..\GUIWindow\InventoryWindow.h"

DropItem::DropItem():
	DeleteTime(300)
{
}

DropItem::~DropItem()
{
}

void DropItem::Init()
{
	Model.Load("chest.X", nullptr);
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());

	Transform.Position.y = 1;
}

void DropItem::Update()
{
	//プレイヤーとの距離を測って
	D3DXVECTOR3 pPos = g_Player->GetPos();
	D3DXVECTOR3 toPlayer = pPos - Transform.Position;
	if (D3DXVec3Length(&toPlayer) <= 3)
	{
		//近い状態で特定のキーが押されたらゲットさせる
		if (Input.GetKeyButton(KeyCode::Z))
		{
			isActive = false;
			IItem* item = new IItem;
			item->Load();
			if (!Inventory().SetItem(item))
			{
				SAFE_DELETE(item);
			}
		}
	}
	Model.Update();

	if (LocalTime >= DeleteTime)
	{
		isActive = false;
	}
	LocalTime += Time().DeltaTime();
}

void DropItem::Render()
{
	Model.Render();
}

void DropItem::Release()
{
	Model.Release();
}
