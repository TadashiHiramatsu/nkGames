#include"stdafx.h"
#include"InventoryWindow.h"

InventoryWindow::InventoryWindow()
{
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::Init()
{
	//Sprite.Load("window.png");
	//Sprite.SetSTransform(&STransform);

	//STransform.Size = D3DXVECTOR2(500, 500);

	IFrameNum = 10;

	IFrameTex.Load("Frame.png");

	for (int i = 0; i < IFrameNum; i++)
	{
		ItemSlot* IS = new ItemSlot;
		IS->Init();
		IS->STransform.Position = D3DXVECTOR2(890, 530 - i * 40);
		IS->Frame.SetTexture(&IFrameTex);

		IFrames.push_back(IS);
	}

	//Test
	IItem* item = new IItem;
	item->Load();

	if (!SetItem(item))
	{
		SAFE_DELETE(item);
	}
}

void InventoryWindow::Update()
{
	//Sprite.Update();
	for (auto a : IFrames)
	{
		a->Update();
	}
}

void InventoryWindow::Render()
{
	//Sprite.Render();
	for (auto a : IFrames)
	{
		a->Render();
	}
}

void InventoryWindow::Release()
{

}

bool InventoryWindow::SetItem(IItem * _item)
{
	for (auto a : IFrames)
	{
		if (a->Item != nullptr)
		{
			if (a->Item->GetID() != _item->GetID())
			{
				//“ü‚ç‚È‚¢‚æ
				return false;
			}
			else
			{
				//‘‚¦‚½‚æ
				a->ItemNum++;
			}
		}
		else
		{
			a->Item = _item;
			a->Item->SetSTramsform(&a->STransform);
			a->Item->Update();
			a->ItemNum++;
			break;
		}
	}
	return true;
}

void ItemSlot::Init()
{
	STransform.Size = D3DXVECTOR2(30, 30);
	STransform.Pivot = D3DXVECTOR2(1, 1);
	Frame.Load();
	Frame.SetSTransform(&STransform);
}

void ItemSlot::Update()
{
	Frame.Update();
	if (Item != nullptr)
	{
		Item->Update();
	}
}

void ItemSlot::Render()
{
	Frame.Render();
	if (Item != nullptr)
	{
		Item->Render();
	}
}
