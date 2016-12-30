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
	Image ItemIcon;

	//ÉtÉåÅ[ÉÄ
	Image Frame;
	RectTransform rectTransform;


	int ItemNum;
};