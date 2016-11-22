#include"stdafx.h"
#include"IItem.h"

IItem::IItem():
	ID(0),
	Name("–¼–³‚µ‚ÌƒAƒCƒeƒ€")
{
}

IItem::~IItem()
{

}

void IItem::Load()
{
	Sprite.Load("NonData.png");
}

void IItem::Init()
{

}

void IItem::Update()
{
	Sprite.Update();
}

void IItem::Render()
{
	Sprite.Render();
}

void IItem::Release()
{

}

void IItem::Click()
{

}
