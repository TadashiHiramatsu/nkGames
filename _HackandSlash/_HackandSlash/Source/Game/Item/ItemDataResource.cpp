/**
 * @file	Source\Game\Item\ItemDataResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemDataResource.h"


/**
* 読み込み.
*/
void CItemDataResource::Load()
{
	LoadFile("ItemData/ArmorItemData");
	LoadFile("ItemData/WeaponItemData");
}

/**
* ファイルの読み込み.
*/
void CItemDataResource::LoadFile(char* filePath)
{
	CSVDataTableT table;

	CSVData csv;
	csv.Load(filePath, table);

	for (int row = 1; row < table.size() -1; row++)
	{
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
		string iconfp = "Icon/" + record[ItemDataReadCodeE::FileName];

		//アイテム名
		string namefp = record[ItemDataReadCodeE::ItemName];

		//最低ドロップレベル
		int minlevel = stoi(record[ItemDataReadCodeE::MinLevel]);
		//最高ドロップレベル
		int maxlevel = stoi(record[ItemDataReadCodeE::MaxLevel]);
		//ドロップ確率
		int probability = stof(record[ItemDataReadCodeE::Probability]) * 10000;

		//タイプによって違う初期化
		switch (type)
		{
		case Weapon:
		{
			int attack = stoi(record[ItemDataReadCodeE::Parameter]);

			//アイテムデータ作成
			item = new WeaponItemData(id, namefp, iconfp, type, minlevel, maxlevel, probability, attack);
			
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
			int defense = stoi(record[ItemDataReadCodeE::Parameter]);
		
			//アイテムデータ作成
			item = new ArmorItemData(id, namefp, iconfp, type, minlevel, maxlevel, probability, defense);
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
