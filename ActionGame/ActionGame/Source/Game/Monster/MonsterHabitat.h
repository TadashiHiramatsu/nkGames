#pragma once

#include"IMonster.h"

//モンスターの住処
//中心地からモンスターは出現する
class MonsterHabitat
{
public:
	struct MHParameter
	{
		D3DXVECTOR3 Position; //中心地
		float Distance; //距離
		int MonsterID; //モンスターの種類
		int MonsterMax; //出現最大数
		float Time; //出現間隔
	}; 
public:
	MonsterHabitat();
	~MonsterHabitat();
	void Init(MHParameter& _mhp);
	void Init();
	void Update();
	void Render();
	void Release();

private:
	MHParameter MHP; //モンスターハンターポータブルじゃないよ
	vector<IMonster*> MonsterList;
	int NowMonsterNum = 0; //現在のモンスター数
	float LocalTime = 0; 
};