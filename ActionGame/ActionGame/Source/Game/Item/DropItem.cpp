#include"stdafx.h"
#include"DropItem.h"

#include"../GameScene.h"
#include"../GameCamera.h"
#include"../Window/InventoryWindow.h"

DropItem::DropItem():
	DeleteTime(300)
{
}

DropItem::~DropItem()
{
}

void DropItem::Start()
{
	SMDResources().Load(SkinModelData, "chest.X", nullptr);

	Model.Load(SkinModelData.GetBody());
	Model.SetTransform(&transform);
	Model.SetLight(&Light);
	Model.SetCamera(g_MainCamera->GetCamera());

}

void DropItem::Update()
{
	//プレイヤーとの距離を測って
	D3DXVECTOR3 pPos = g_Player->GetPos();
	D3DXVECTOR3 toPlayer = pPos - transform.Position;
	if (D3DXVec3Length(&toPlayer) <= 3)
	{
		//近い状態で特定のキーが押されたらゲットさせる
		if (Input.GetKeyButtonDown(KeyCode::Z))
		{
			DeleteGO(this);
			IItem* item = new EquipmentItem;
			item->Load();
			if (!g_Inventory->SetItem(item))
			{
				SAFE_DELETE(item);
			}
		}
	}

	transform.Update();

	Model.Update();

	if (LocalTime >= DeleteTime)
	{
		DeleteGO(this);
	}
	LocalTime += Time().DeltaTime();
}

void DropItem::Render()
{
	Model.Render();
}
