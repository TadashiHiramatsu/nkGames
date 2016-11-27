#include"stdafx.h"
#include"MonsterHabitat.h"

#include"Monster_01.h"

MonsterHabitat::MonsterHabitat()
{
}

MonsterHabitat::~MonsterHabitat()
{
}

void MonsterHabitat::Init(MHParameter& _mhp)
{
	MHP = _mhp;
}

void MonsterHabitat::Init()
{
	MHP.Distance = 10;
	MHP.MonsterID = 1;
	MHP.MonsterMax = 10;
	MHP.Position = D3DXVECTOR3(0, 1, 0);
	MHP.Time = 5;
}

void MonsterHabitat::Update()
{
	if (NowMonsterNum <= MHP.MonsterMax)
	{
		if (MHP.Time <= LocalTime)
		{
			Monster_01* m = new Monster_01;
			m->Init();
			MonsterList.push_back(m);
			NowMonsterNum++;
			LocalTime = 0;
		}
		LocalTime += Time().DeltaTime();
	}

	auto it = MonsterList.begin();
	while (it != MonsterList.end())
	{
		(*it)->Update();
		if (!(*it)->GetActive())
		{
			NowMonsterNum--;
			delete (*it);
			it = MonsterList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MonsterHabitat::Render()
{
	for (auto it : MonsterList)
	{
		it->Render();
	}
}

void MonsterHabitat::Release()
{
}
