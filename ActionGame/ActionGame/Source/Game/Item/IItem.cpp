#include"stdafx.h"
#include"IItem.h"

IItem::IItem()
{
}

IItem::~IItem()
{

}

void IItem::Load()
{
	Image.Load(IP.IconFilePath);
}

void IItem::Init()
{

}

void IItem::Render()
{
	Image.Render();
}

void IItem::Release()
{

}

