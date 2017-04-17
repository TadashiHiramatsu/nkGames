/**
* �A�C�e���̊��N���X�̎���.
*/
#include"stdafx.h"
#include"IItemData.h"

/**
* �R���X�g���N�^.
*
* @param id			 	�A�C�e��ID.
* @param itemname		�A�C�e����.
* @param iconfilename	�A�C�R���t�@�C����.
* @param type		 	�A�C�e���^�C�v.
* @param minlevel	 	�Œ჌�x��.
* @param maxlevel	 	�ō����x��.
* @param probability	�h���b�v��.
*/
IItemData::IItemData(int id, const string& itemname, const string& iconfilename,ItemTypeE type,int minlevel, int maxlevel,int probability) :
	ItemID_(id),
	Name_(itemname),
	IconFilePath_(iconfilename),
	Type_(type),
	MinLevel_(minlevel),
	MaxLevel_(maxlevel),
	Probability_(probability)
	{
	}
