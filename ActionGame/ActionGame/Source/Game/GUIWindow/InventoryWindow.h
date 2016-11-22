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
	SpriteTransform STransform;

	CSprite Frame;

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
	void Release()override;

	bool SetItem(IItem* _item);

private:
	//CSprite Sprite;
	//SpriteTransform STransform;

	int IFrameNum;
	CTexture IFrameTex;
	vector<ItemSlot*> IFrames;
};

static InventoryWindow& Inventory()
{
	return InventoryWindow::GetInstance();
}