#include"stdafx.h"
#include"ItemSlot.h"

void ItemSlot::Start()
{
	rectTransform.Width = 30;
	rectTransform.Height = 30;
	rectTransform.Pivot = D3DXVECTOR2(0.5, 0.5);
	Frame.Load();
	Frame.SetTransform(&rectTransform);
}

void ItemSlot::Update()
{
	rectTransform.Update();
}

void ItemSlot::Render()
{
	if (Item != nullptr)
	{
		ItemIcon.Render();
	}
	Frame.Render();
}
