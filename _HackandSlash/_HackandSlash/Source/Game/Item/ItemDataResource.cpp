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

		vector<string> record; //1行分
		record = table[row]; //1行分読み込み

		//ID計算
		int id = 0;
		//上一桁
		id += (int)IItemData::Armor * IItemData::TypeID;
		//上2桁目
		id += stoi(record[3]) * IItemData::SubTypeID;
		//下3桁
		id += stoi(record[0]);

		IItemData* item = nullptr;

		const char* baseDir = "Icon/";
		char iconfp[64];
		strcpy(iconfp, baseDir);
		strcat(iconfp, record[2].c_str());

		char namefp[64];
		strcpy(namefp, record[1].c_str());


		//タイプによって違う初期化
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
			//アイテムデータ作成
			item = new ArmorItemData(id, namefp, iconfp, type, defense);
		}
		break;
		case IItemData::Accessory:
			break;
		}
		//登録
		ItemList.insert(make_pair(id, item));

	}
}
