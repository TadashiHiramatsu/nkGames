/**
 * @file	Source\Game\Item\Armor.cpp
 *
 * Implements the armor class.
 */
#include"stdafx.h"
#include"Armor.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
Armor::Armor()
{
	Type = ItemType::Armor;
}

/**
 * Constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2017/01/05
 *
 * @param	_ID			 	The identifier.
 * @param	_Name		 	The name.
 * @param	_IconFilePath	Full pathname of the icon file.
 * @param	_Rarity		 	The rarity.
 * @param	_AType		 	The type.
 * @param	_Defense	 	The defense.
 */
Armor::Armor(int _ID, const char * _Name, const char * _IconFilePath, RarityCode _Rarity, ArmorType _AType, int _Defense)
{
	ID = _ID;
	Name = _Name;
	IconFilePath = _IconFilePath;
	Rarity = _Rarity;
	AType = _AType;
	Defense = _Defense;
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
Armor::~Armor()
{
}
