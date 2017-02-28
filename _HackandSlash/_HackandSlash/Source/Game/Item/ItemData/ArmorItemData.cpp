/**
 * @file	Source\Game\Item\ArmorItemDataItem.cpp
 *
 * Implements the ArmorItemData class.
 */
#include"stdafx.h"
#include"ArmorItemData.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
ArmorItemData::ArmorItemData()
{
	Type_ = ItemTypeE::Helm;
	Defense_ = 1;
}

/**
* Constructor.
*
* @author	HiramatsuTadashi
* @date	2017/01/05
*
* @param	id			 	アイテムID.
* @param	itemname		アイテム名.
* @param	iconfilename	アイコンファイル名.
* @param	type		 	アイテムタイプ.
* @param	defense	 		防御力.
* @param	minlevel	 	最低レベル.
* @param	maxlevel	 	最高レベル.
* @param	probability	 	ドロップ率.
*/
ArmorItemData::ArmorItemData(int id, char * itemname, char * iconfilename, ItemTypeE type, int defense, int minlevel, int maxlevel, int probability)
{
	ID_ = id;

	strcpy(Name_, itemname);
	strcpy(IconFilePath_, iconfilename);

	Type_ = type;

	Defense_ = defense;

	MinLevel_ = minlevel;
	MaxLevel_ = maxlevel;
	Probability_ = probability;
}
