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

		//�A�C�e���f�[�^
		IItemData* item = nullptr;

		vector<string> record; //1�s��
		record = table[row]; //1�s���ǂݍ���

		//�A�C�e���^�C�v
		ItemTypeE type = (ItemTypeE)(stoi(record[ItemDataReadCodeE::ItemType]));

		//ID�v�Z
		int id = 0;
		//��1��
		id += (type + 1) * IItemData::TypeID;
		//��3��
		id += stoi(record[ItemDataReadCodeE::ItemID]);

		//�A�C�R���t�@�C����
		const char* baseDir = "Icon/";
		char iconfp[64];
		strcpy(iconfp, baseDir);
		strcat(iconfp, record[ItemDataReadCodeE::FileName].c_str());

		//�A�C�e����
		char namefp[64];
		strcpy(namefp, record[ItemDataReadCodeE::ItemName].c_str());

		//�Œ�h���b�v���x��
		int minlevel = stoi(record[ItemDataReadCodeE::MinLevel]);
		//�ō��h���b�v���x��
		int maxlevel = stoi(record[ItemDataReadCodeE::MaxLevel]);
		//�h���b�v�m��
		int probability = stoi(record[ItemDataReadCodeE::Probability]);

		//�^�C�v�ɂ���ĈႤ������
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
		
			//�A�C�e���f�[�^�쐬
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
		
		//�o�^
		ItemList.insert(make_pair(id, item));

	}
}
