#pragma once

#include"IMonster.h"

//モンスターの住処
//中心地からモンスターは出現する
class MonsterHabitat : public IGameObject
{
public:

	//MonsterHabitatクラスのパラメータ
	struct MHParameter
	{
		MHParameter()
		{
			Position = D3DXVECTOR3(0, 1, 0);
			Distance = 10;
			MonsterID = 1;
			MonsterMax = 10;
			Time = 5;
			InitMonsterNum = 5;
		}
		D3DXVECTOR3 Position; //中心地
		float Distance; //距離
		int MonsterID; //モンスターの種類
		int MonsterMax; //出現最大数
		float Time; //出現間隔
		int InitMonsterNum; //初期化時のモンスターの数
	};

public:

	//コンストラクタ
	MonsterHabitat();
	//デストラクタ
	~MonsterHabitat();

public:

	//初期化
	void Start()override;
	//更新
	void Update()override;
	//描画
	void Render()override;

	//モンスター出現関数
	void Appearance();

private:
	MHParameter Parameter; //モンスターハンターポータブルじゃないよ
	vector<IMonster*> MonsterList;
	int NowMonsterNum = 0; //現在のモンスター数
	float LocalTime = 0; 
};