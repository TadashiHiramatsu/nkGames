#include"stdafx.h"
#include"MonsterHabitat.h"

#include"Monster_01.h"

MonsterHabitat::MonsterHabitat()
{
}

MonsterHabitat::~MonsterHabitat()
{
}

void MonsterHabitat::Start()
{
	for (int i = 0; i < Parameter.InitMonsterNum; i++)
	{
		Appearance();
	}
}

void MonsterHabitat::Update()
{
	if (NowMonsterNum <= Parameter.MonsterMax)
	{
		if (Parameter.Time <= LocalTime)
		{
			Appearance();
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

void MonsterHabitat::Appearance()
{
	Monster_01* m = new Monster_01;

	D3DXVECTOR3 pos = D3DXVECTOR3(Random().GetRandDouble0() * Parameter.Distance, 0, Random().GetRandDouble0() * Parameter.Distance);
	pos += Parameter.Position;
	m->SetPosition(pos);

	m->Start();

	MonsterList.push_back(m);
	NowMonsterNum++;
	LocalTime = 0;
}
