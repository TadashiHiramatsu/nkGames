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
* @param	defense	 		�h���.
* @param	minlevel	 	�Œ჌�x��.
* @param	maxlevel	 	�ō����x��.
* @param	probability	 	�h���b�v��.
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
