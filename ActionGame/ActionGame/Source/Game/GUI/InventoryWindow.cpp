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
	IWSkin.Load("Image/window.png");
	IWSkin.SetTransform(&rectTransform);

	rectTransform.Width = 250;
	rectTransform.Height = 500;

	ISlotNum = 40;

	IFrameTex.reset(new CTexture);
	IFrameTex->Load("Image/Frame.png");

	//i:列,j:行
	for (int i = 0 , j = 0; i < ISlotNum; i++)
	{
		if (i % 5 == 0)
		{
			//横に５列進んだので行を変える
			j++;
		}

		//ItemSlotを作成
		ItemSlot* IS = new ItemSlot;
		//初期化
		IS->Start();

		//位置を設定
		float x, y;
		x = -80 + (i % 5) * 40; //初期値 + 横にずらす値
		y = 170 + j * -40; //初期値 + 縦にずらす値
		IS->rectTransform.Position = D3DXVECTOR2(x,y);
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

//bool InventoryWindow::SetItem(IItem * _item)
//{
//	for (auto it : ISlotVec)
//	{
//		if (it->Item != nullptr)
//		{
//			if (it->Item->GetParameter().ID != _item->GetParameter().ID)
//			{
//				//入らないよ
//				return false;
//			}
//			else
//			{
//				//増えたよ
//				it->ItemNum++;
//				break;
//			}
//		}
//		else
//		{
//			//新しくセットするよ
//			it->Item = _item;
//			it->ItemIcon.Load(_item->GetParameter().IconFilePath);
//			it->ItemNum++;
//			break;
//		}
//	}
//	return true;
//}
