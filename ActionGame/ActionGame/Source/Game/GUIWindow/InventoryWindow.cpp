#include"stdafx.h"
#include"InventoryWindow.h"

InventoryWindow::InventoryWindow():
	isRender(false)
{
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::Init()
{
	IWSkin.Load("window.png");
	IWSkin.SetTransform(&IWSkinTransform);

	IWSkinTransform.Size = D3DXVECTOR2(500, 500);
	IWSkinTransform.Position.x = Engine().GetScreenW() / 2;
	IWSkinTransform.Position.y = Engine().GetScreenH() / 2;

	ISlotNum = 10;

	IFrameTex.reset(new CTexture);
	IFrameTex->Load("Icon/Frame.png");

	for (int i = 0; i < ISlotNum; i++)
	{
		ItemSlot* IS = new ItemSlot;
		IS->Init();
		IS->Transform.Position = D3DXVECTOR2(0,i * 40);
		IS->Frame.SetTexture(IFrameTex);
		ISlotVec.push_back(IS);
	}
}

void InventoryWindow::Update()
{
	if (Input.GetKeyButtonDown(KeyCode::I))
	{
		isRender = !isRender;
	}

	if (isRender)
	{
		IWSkin.Update();
		for (auto a : ISlotVec)
		{
			a->Update();
		}
	}
}

void InventoryWindow::Render()
{
	if (isRender)
	{
		IWSkin.Render();
		for (auto a : ISlotVec)
		{
			a->Render();
		}
	}
}

bool InventoryWindow::SetItem(IItem * _item)
{
	for (auto it : ISlotVec)
	{
		if (it->Item != nullptr)
		{
			if (it->Item->GetParameter().ID != _item->GetParameter().ID)
			{
				//“ü‚ç‚È‚¢‚æ
				return false;
			}
			else
			{
				//‘‚¦‚½‚æ
				it->ItemNum++;
				break;
			}
		}
		else
		{
			it->Item = _item;
			it->Item->SetSTramsform(&it->Transform);
			it->Item->Update();
			it->ItemNum++;
			break;
		}
	}
	return true;
}

void ItemSlot::Init()
{
	Transform.Size = D3DXVECTOR2(30, 30);
	Transform.Pivot = D3DXVECTOR2(1, 1);
	Frame.Load();
	Frame.SetTransform(&Transform);
}

void ItemSlot::Update()
{
	Transform.Update();
	if (Item != nullptr)
	{
		Item->Update();
	}
	Frame.Update();
}

void ItemSlot::Render()
{
	if (Item != nullptr)
	{
		Item->Render();
	}
	Frame.Render();
}
