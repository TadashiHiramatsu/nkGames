/**
 * @file Source\Game\GUI\ItemSlot.h
 *
 * アイテムスロットクラスの定義.
 */
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

	//フレーム
	Image Frame;
	RectTransform rectTransform;


	int ItemNum;
};