#include"stdafx.h"
#include"DropItemManager.h"

DropItemManager::DropItemManager()
{

}

DropItemManager::~DropItemManager()
{

}

void DropItemManager::Init()
{
	DIvector.clear();
}

void DropItemManager::Update()
{
	auto it = DIvector.begin();
	while (it != DIvector.end())
	{
		(*it)->Update();
		if (!(*it)->GetActive())
		{
			delete (*it);
			it = DIvector.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void DropItemManager::Render()
{
	for (auto a : DIvector)
	{
		a->Render();
	}
}

void DropItemManager::Release()
{

}
