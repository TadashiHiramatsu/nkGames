#pragma once

#include"IWindow.h"
#include"../Item/IItem.h"

class ItemSlot
{
public:
	ItemSlot() :
		Item(nullptr),
		ItemNum(0)
	{

	}

	void Init();
	void Update();
	void Render();

public:
	IItem* Item;
	UITransform Transform;

	Image Frame;

	int ItemNum;
};

class InventoryWindow : public IWindow
{
private:
	InventoryWindow();
	~InventoryWindow();
public:
	static InventoryWindow& GetInstance()
	{
		static InventoryWindow instance;
		return instance;
	}

	void Init()override;
	void Update()override;
	void Render()override;

	bool SetItem(IItem* _item);

private:
	Image IWSkin;
	UITransform IWSkinTransform;

	int ISlotNum;
	shared_ptr<CTexture> IFrameTex;
	vector<ItemSlot*> ISlotVec;

	bool isRender;
};

static InventoryWindow& Inventory()
{
	return InventoryWindow::GetInstance();
}