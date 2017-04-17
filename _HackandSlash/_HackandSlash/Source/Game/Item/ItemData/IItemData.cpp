/**
* アイテムの基底クラスの実装.
*/
#include"stdafx.h"
#include"IItemData.h"

/**
* コンストラクタ.
*
* @param id			 	アイテムID.
* @param itemname		アイテム名.
* @param iconfilename	アイコンファイル名.
* @param type		 	アイテムタイプ.
* @param minlevel	 	最低レベル.
* @param maxlevel	 	最高レベル.
* @param probability	ドロップ率.
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
