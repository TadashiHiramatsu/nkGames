/**
 * @file	Source\Game\Item\ItemDataResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemDataResource.h"

#include"../../Test/Item/ItemType.h"

void CItemDataResource::Load()
{
	LoadFile("ArmorItemData.csv");
}

void CItemDataResource::LoadFile(char * filePath)
{
	vector<vector<string>> table;

	CSVData csv;
	csv.Load(filePath, table);

	for (int row = 1; row < table.size() -1; row++)
	{

		vector<string> record; //1�s��
		record = table[row]; //1�s���ǂݍ���

		ItemTypeE type = (ItemTypeE)(stoi(record[3]));

		//ID�v�Z
		int id = 0;
		//��1��
		id += (type + 1) * IItemData::SubTypeID;
		//��3��
		id += stoi(record[0]);

		IItemData* item = nullptr;

		const char* baseDir = "Icon/";
		char iconfp[64];
		strcpy(iconfp, baseDir);
		strcat(iconfp, record[2].c_str());

		char namefp[64];
		strcpy(namefp, record[1].c_str());

		//�^�C�v�ɂ���ĈႤ������
		switch (type)
		{
		case Sword:
			break;
		case Shield:
			break;
		case Helm:
		case Armor:
		case Arm:
		case Greaves:
		{
			int defense = stoi(record[4]);
			//�A�C�e���f�[�^�쐬
			item = new ArmorItemData(id, namefp, iconfp, type, defense);
		}
		break;
		case Accessory:
			break;
		case TypeNum:
			break;
		default:
			break;
		}
		
		//�o�^
		ItemList.insert(make_pair(id, item));

	}
}
