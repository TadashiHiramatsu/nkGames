#include"stdafx.h"
#include"InventoryWindow.h"

InventoryWindow::InventoryWindow():
	isRender(false)
{
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::Start()
{
	IWSkin.Load("window.png");
	IWSkin.SetTransform(&rectTransform);

	rectTransform.Width = 500;
	rectTransform.Height = 500;

	ISlotNum = 40;

	IFrameTex.reset(new CTexture);
	IFrameTex->Load("Icon/Frame.png");

	for (int i = 0 , j = 0; i < ISlotNum; i++)
	{
		if (i % 5 == 0)
		{
			j++;
		}

		ItemSlot* IS = new ItemSlot;
		IS->Start();
		IS->rectTransform.Position = D3DXVECTOR2(20 + (i % 5) * 40, 170 + j * -40);
		IS->rectTransform.Parent = &rectTransform;
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
		rectTransform.Update();
		for (auto it : ISlotVec)
		{
			it->Update();
		}
	}
}

void InventoryWindow::Render()
{
	if (isRender)
	{
		IWSkin.Render();
		for (auto it : ISlotVec)
		{
			it->Render();
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
				//入らないよ
				return false;
			}
			else
			{
				//増えたよ
				it->ItemNum++;
				break;
			}
		}
		else
		{
			//新しくセットするよ
			it->Item = _item;
			it->Item->SetSTramsform(&it->rectTransform);
			it->Item->Update();
			it->ItemNum++;
			break;
		}
	}
	return true;
}
