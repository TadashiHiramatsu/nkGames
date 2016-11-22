#pragma once

#include"DropItem.h"

class DropItemManager
{
private:
	DropItemManager();
	~DropItemManager();
public:
	static DropItemManager& GetInstance()
	{
		static DropItemManager instance;
		return instance;
	}

	void Init();
	void Update();
	void Render();
	void Release();

	void SetDropItem(DropItem* _di)
	{
		DIvector.push_back(_di);
	}

private:
	vector<DropItem*> DIvector;
};

static DropItemManager& DIManager()
{
	return DropItemManager::GetInstance();
}