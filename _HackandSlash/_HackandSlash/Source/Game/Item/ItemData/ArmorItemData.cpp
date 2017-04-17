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
* @param	minlevel	 	最低レベル.
* @param	maxlevel	 	最高レベル.
* @param	probability	 	ドロップ率.
* @param	defense	 		防御力.
*/
ArmorItemData::ArmorItemData(int id, const string& itemname, const string& iconfilename, ItemTypeE type, int minlevel, int maxlevel, int probability, int defense) :
	IItemData(id,itemname,iconfilename,type,minlevel,maxlevel,probability)
{
	Defense_ = defense;
}
