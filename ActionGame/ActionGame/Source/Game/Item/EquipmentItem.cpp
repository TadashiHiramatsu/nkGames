#include"stdafx.h"
#include"EquipmentItem.h"

EquipmentItem::EquipmentItem()
{
}

EquipmentItem::~EquipmentItem()
{
}

void EquipmentItem::Load()
{
	IP.IconFilePath = "Icon/sword.png";
	IItem::Load();
}

void EquipmentItem::Init()
{
	IItem::Init();
}

void EquipmentItem::Update()
{
	IItem::Update();
}

void EquipmentItem::Render()
{
	IItem::Render();
}

void EquipmentItem::Release()
{
	IItem::Release();
}

void EquipmentItem::Click()
{
}
