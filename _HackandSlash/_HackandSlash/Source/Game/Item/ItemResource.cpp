/**
 * @file	Source\Game\Item\ItemResource.cpp
 *
 * Implements the item resource class.
 */
#include"stdafx.h"
#include"ItemResource.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
CItemResource::CItemResource()
{
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/03
 */
CItemResource::~CItemResource()
{
}

void CItemResource::Load()
{
	LoadFile("ArmorData.csv", IItem::ItemType::Armor);
}

void CItemResource::LoadFile(char * _FilePath, IItem::ItemType _Type)
{
	vector<vector<string>> table;

	CSVData csv;
	csv.Load(_FilePath, table);

	for (int row = 1; row < table.size(); row++)
	{
		vector<string> record; //1�s��
		record = table[row]; //1�s���ǂݍ���
		for (int column = 0; column < record.size(); column++)
		{
			//ID�v�Z
			int id = 0;
			//��ꌅ
			id += (int)IItem::Armor * IItem::TypeID;
			//��2����
			id += stoi(record[3]) * IItem::SubTypeID;
			//��3��
			id += stoi(record[0]);

			IItem* item = nullptr;

			//�^�C�v�ɂ���ĈႤ������
			switch (_Type)
			{
			case IItem::Weapon:
				break;
			case IItem::Armor:
				//�A�C�e���f�[�^�쐬
				item = new Armor(id, record[1].c_str(), record[2].c_str(), (IItem::RarityCode)stoi(record[4]), (Armor::ArmorType)stoi(record[3]), stoi(record[5]));
				break;
			case IItem::Other:
				break;
			}
			//�o�^
			ItemList.insert(make_pair(id, item));
		}
	}
}
