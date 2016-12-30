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

	//i:��,j:�s
	for (int i = 0 , j = 0; i < ISlotNum; i++)
	{
		if (i % 5 == 0)
		{
			//���ɂT��i�񂾂̂ōs��ς���
			j++;
		}

		//ItemSlot���쐬
		ItemSlot* IS = new ItemSlot;
		//������
		IS->Start();

		//�ʒu��ݒ�
		float x, y;
		x = -80 + (i % 5) * 40; //�����l + ���ɂ��炷�l
		y = 170 + j * -40; //�����l + �c�ɂ��炷�l
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
//				//����Ȃ���
//				return false;
//			}
//			else
//			{
//				//��������
//				it->ItemNum++;
//				break;
//			}
//		}
//		else
//		{
//			//�V�����Z�b�g�����
//			it->Item = _item;
//			it->ItemIcon.Load(_item->GetParameter().IconFilePath);
//			it->ItemNum++;
//			break;
//		}
//	}
//	return true;
//}
