#include"stdafx.h"
#include"EnemySpawnManager.h"

void EnemySpawnManager::Start()
{
	CSVDataTableT table;
	CSVData::Load("EnemySpawnData/EnemySpawnData_01", table);

	for (int i = 1; i < table.size() - 1; i++)
	{
		vector<string> record = table[i]; //1çsï™

		EnemySpawnInfoS Info;
		Info.Position_.x = stof(record[ESReadCodeE::PositionX]);
		Info.Position_.y = stof(record[ESReadCodeE::PositionY]);
		Info.Position_.z = stof(record[ESReadCodeE::PositionZ]);
		Info.Distance_ = stof(record[ESReadCodeE::Distance]);
		Info.EnemyMax_ = stoi(record[ESReadCodeE::EnemyMax]);
		Info.SpawnTime_ = stof(record[ESReadCodeE::SpawnTime]);
		Info.EnemyLevel_ = stoi(record[ESReadCodeE::EnemyLevel]);
		Info.EnemyID_ = stoi(record[ESReadCodeE::EnemyID]);

		EnemySpawn* es = NewGO<EnemySpawn>(1);
		es->Start(Info);
		es->SetPlayer(Player_);

		//í«â¡
		EnemySpawnList_.push_back(es);

	}

}
