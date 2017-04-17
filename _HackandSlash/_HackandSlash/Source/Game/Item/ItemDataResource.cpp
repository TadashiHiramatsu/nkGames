/**
 * @file	Source\Game\Item\ItemDataResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemDataResource.h"


/**
* �ǂݍ���.
*/
void CItemDataResource::Load()
{
	LoadFile("ItemData/ArmorItemData");
	LoadFile("ItemData/WeaponItemData");
}

/**
* �t�@�C���̓ǂݍ���.
*/
void CItemDataResource::LoadFile(char* filePath)
{
	CSVDataTableT table;

	CSVData csv;
	csv.Load(filePath, table);

	for (int row = 1; row < table.size() -1; row++)
	{
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
		string iconfp = "Icon/" + record[ItemDataReadCodeE::FileName];

		//�A�C�e����
		string namefp = record[ItemDataReadCodeE::ItemName];

		//�Œ�h���b�v���x��
		int minlevel = stoi(record[ItemDataReadCodeE::MinLevel]);
		//�ō��h���b�v���x��
		int maxlevel = stoi(record[ItemDataReadCodeE::MaxLevel]);
		//�h���b�v�m��
		int probability = stof(record[ItemDataReadCodeE::Probability]) * 10000;

		//�^�C�v�ɂ���ĈႤ������
		switch (type)
		{
		case Weapon:
		{
			int attack = stoi(record[ItemDataReadCodeE::Parameter]);

			//�A�C�e���f�[�^�쐬
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
		
			//�A�C�e���f�[�^�쐬
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
		
		//�o�^
		ItemList.insert(make_pair(id, item));

	}
}
