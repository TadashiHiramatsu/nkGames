/**
 * @file	Source\Game\Item\ItemDataResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemDataResource.h"

void CItemDataResource::Load()
{
	LoadFile("ArmorItemData.csv", IItemData::ItemTypeE::Armor);
}

void CItemDataResource::LoadFile(char * filePath, IItemData::ItemTypeE type)
{
	vector<vector<string>> table;

	CSVData csv;
	csv.Load(filePath, table);

	for (int row = 1; row < table.size() -1; row++)
	{

		vector<string> record; //1�s��
		record = table[row]; //1�s���ǂݍ���

		//ID�v�Z
		int id = 0;
		//��ꌅ
		id += (int)IItemData::Armor * IItemData::TypeID;
		//��2����
		id += stoi(record[3]) * IItemData::SubTypeID;
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
		case IItemData::Sword:
			break;
		case IItemData::Shield:
			break;
		case IItemData::Armor:
		{
			ArmorItemData::ArmorItemTypeE type = (ArmorItemData::ArmorItemTypeE)stoi(record[3]);
			int defense = stoi(record[4]);
			//�A�C�e���f�[�^�쐬
			item = new ArmorItemData(id, namefp, iconfp, type, defense);
		}
		break;
		case IItemData::Accessory:
			break;
		}
		//�o�^
		ItemList.insert(make_pair(id, item));

	}
}
