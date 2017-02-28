/**
 * @file	Source\Game\Item\ItemDataResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemDataResource.h"

void CItemDataResource::Load()
{
	LoadFile("ItemData/ArmorItemData");
}

void CItemDataResource::LoadFile(char * filePath)
{
	CSVDataTableT table;

	CSVData csv;
	csv.Load(filePath, table);

	for (int row = 1; row < table.size() -1; row++)
	{

		//アイテムデータ
		IItemData* item = nullptr;

		vector<string> record; //1行分
		record = table[row]; //1行分読み込み

		//アイテムタイプ
		ItemTypeE type = (ItemTypeE)(stoi(record[ItemDataReadCodeE::ItemType]));

		//ID計算
		int id = 0;
		//上1桁
		id += (type + 1) * IItemData::TypeID;
		//下3桁
		id += stoi(record[ItemDataReadCodeE::ItemID]);

		//アイコンファイル名
		const char* baseDir = "Icon/";
		char iconfp[64];
		strcpy(iconfp, baseDir);
		strcat(iconfp, record[ItemDataReadCodeE::FileName].c_str());

		//アイテム名
		char namefp[64];
		strcpy(namefp, record[ItemDataReadCodeE::ItemName].c_str());

		//最低ドロップレベル
		int minlevel = stoi(record[ItemDataReadCodeE::MinLevel]);
		//最高ドロップレベル
		int maxlevel = stoi(record[ItemDataReadCodeE::MaxLevel]);
		//ドロップ確率
		int probability = stoi(record[ItemDataReadCodeE::Probability]);

		//タイプによって違う初期化
		switch (type)
		{
		case Sword:
		{

		}
		break;
		case Shield:
		{

		}
		break;
		case Helm:
		case Armor:
		case Arm:
		case Greaves:
		{
			int defense = stoi(record[ItemDataReadCodeE::Defense]);
		
			//アイテムデータ作成
			item = new ArmorItemData(id, namefp, iconfp, type, defense, minlevel, maxlevel, probability);
		}
		break;
		case Accessory:
		{

		}
		break;
		default:
			break;
		}
		
		//登録
		ItemList.insert(make_pair(id, item));

	}
}
