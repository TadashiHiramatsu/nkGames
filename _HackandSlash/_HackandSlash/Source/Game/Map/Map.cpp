#include"stdafx.h"
#include"Map.h"

/**
* 初期化.
*/
void Map::Start()
{
	CSVDataTableT table;
	CSVData::Load("MapData/Map_01", table);

	vector<MapChipInfoS*> MapChipInfoList;

	for (int row = 1; row < table.size() - 1; row++)
	{
		vector<string> record; //1行分
		record = table[row]; //1行分読み込み

		MapChipInfoS* mapchipinfo = new MapChipInfoS();

		//モデル名設定
		mapchipinfo->ModelName_ = record[MapChipInfoCode::ModelName];

		//位置読み込み
		D3DXVECTOR3 pos;
		pos.x = stof(record[MapChipInfoCode::PositionX]);
		pos.y = stof(record[MapChipInfoCode::PositionY]);
		pos.z = stof(record[MapChipInfoCode::PositionZ]);
		//位置設定
		mapchipinfo->Transform_.Position_ = pos;

		//回転読み込み
		D3DXQUATERNION rot;
		rot.x = stof(record[MapChipInfoCode::RotationX]);
		rot.y = stof(record[MapChipInfoCode::RotationY]);
		rot.z = stof(record[MapChipInfoCode::RotationZ]);
		rot.w = stof(record[MapChipInfoCode::RotationW]);
		//回転設定
		mapchipinfo->Transform_.Rotation_ = rot;

		//拡大読み込み
		D3DXVECTOR3 scale;
		scale.x = stof(record[MapChipInfoCode::ScaleX]);
		scale.y = stof(record[MapChipInfoCode::ScaleY]);
		scale.z = stof(record[MapChipInfoCode::ScaleZ]);
		//拡大設定
		mapchipinfo->Transform_.Scale_ = scale;

		MapChipInfoList.push_back(mapchipinfo);
	}

	map<string, vector<MapChipInfoS*>*> ModelMap;
	for (int i = 0; i < MapChipInfoList.size(); i++)
	{
		auto& it = ModelMap.find(MapChipInfoList[i]->ModelName_);
		if (it != ModelMap.end())
		{
			//この名前のモデルは登録済み
			it->second->push_back(MapChipInfoList[i]);
		}
		else
		{
			//新規モデル
			vector<MapChipInfoS*>* newList = new vector<MapChipInfoS*>();
			newList->push_back(MapChipInfoList[i]);
			ModelMap.insert(make_pair(MapChipInfoList[i]->ModelName_, newList));
		}
	}

	for (auto mapchiplist : ModelMap)
	{
		//マップチップを作成
		MapChip* mapchip = NewGO<MapChip>();
		mapchip->Start(*mapchiplist.second);
		MapChipList_.push_back(mapchip);
		delete mapchiplist.second;
	}
}
