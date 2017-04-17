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
* @param	id			 	�A�C�e��ID.
* @param	itemname		�A�C�e����.
* @param	iconfilename	�A�C�R���t�@�C����.
* @param	type		 	�A�C�e���^�C�v.
* @param	minlevel	 	�Œ჌�x��.
* @param	maxlevel	 	�ō����x��.
* @param	probability	 	�h���b�v��.
* @param	defense	 		�h���.
*/
ArmorItemData::ArmorItemData(int id, const string& itemname, const string& iconfilename, ItemTypeE type, int minlevel, int maxlevel, int probability, int defense) :
	IItemData(id,itemname,iconfilename,type,minlevel,maxlevel,probability)
{
	Defense_ = defense;
}
