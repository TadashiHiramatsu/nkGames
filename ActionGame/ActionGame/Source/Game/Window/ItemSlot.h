#pragma once

#include"../Item/IItem.h"

class ItemSlot
{
public:
	ItemSlot() :
		Item(nullptr),
		ItemNum(0)
	{

	}

	void Start();
	void Update();
	void Render();

public:
	IItem* Item;
	RectTransform rectTransform;

	Image Frame;

	int ItemNum;
};