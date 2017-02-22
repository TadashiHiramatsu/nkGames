#include"stdafx.h"
#include"Map.h"

/**
* ������.
*/
void Map::Start()
{
	CSVDataTableT table;
	CSVData::Load("MapData/Map_01", table);

	vector<MapChipInfoS*> MapChipInfoList;

	for (int row = 1; row < table.size() - 1; row++)
	{
		vector<string> record; //1�s��
		record = table[row]; //1�s���ǂݍ���

		MapChipInfoS* mapchipinfo = new MapChipInfoS();

		//���f�����ݒ�
		mapchipinfo->ModelName_ = record[MapChipInfoCode::ModelName];

		//�ʒu�ǂݍ���
		D3DXVECTOR3 pos;
		pos.x = stof(record[MapChipInfoCode::PositionX]);
		pos.y = stof(record[MapChipInfoCode::PositionY]);
		pos.z = stof(record[MapChipInfoCode::PositionZ]);
		//�ʒu�ݒ�
		mapchipinfo->Transform_.Position_ = pos;

		//��]�ǂݍ���
		D3DXQUATERNION rot;
		rot.x = stof(record[MapChipInfoCode::RotationX]);
		rot.y = stof(record[MapChipInfoCode::RotationY]);
		rot.z = stof(record[MapChipInfoCode::RotationZ]);
		rot.w = stof(record[MapChipInfoCode::RotationW]);
		//��]�ݒ�
		mapchipinfo->Transform_.Rotation_ = rot;

		//�g��ǂݍ���
		D3DXVECTOR3 scale;
		scale.x = stof(record[MapChipInfoCode::ScaleX]);
		scale.y = stof(record[MapChipInfoCode::ScaleY]);
		scale.z = stof(record[MapChipInfoCode::ScaleZ]);
		//�g��ݒ�
		mapchipinfo->Transform_.Scale_ = scale;

		MapChipInfoList.push_back(mapchipinfo);
	}

	map<string, vector<MapChipInfoS*>*> ModelMap;
	for (int i = 0; i < MapChipInfoList.size(); i++)
	{
		auto& it = ModelMap.find(MapChipInfoList[i]->ModelName_);
		if (it != ModelMap.end())
		{
			//���̖��O�̃��f���͓o�^�ς�
			it->second->push_back(MapChipInfoList[i]);
		}
		else
		{
			//�V�K���f��
			vector<MapChipInfoS*>* newList = new vector<MapChipInfoS*>();
			newList->push_back(MapChipInfoList[i]);
			ModelMap.insert(make_pair(MapChipInfoList[i]->ModelName_, newList));
		}
	}

	for (auto mapchiplist : ModelMap)
	{
		//�}�b�v�`�b�v���쐬
		MapChip* mapchip = NewGO<MapChip>();
		mapchip->Start(*mapchiplist.second);
		MapChipList_.push_back(mapchip);
		delete mapchiplist.second;
	}
}
