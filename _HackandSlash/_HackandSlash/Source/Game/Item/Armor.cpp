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
	Type_ = ItemTypeE::Armor;
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
Armor::Armor(int _ID, char * _Name, char * _IconFilePath, RarityCodeE _Rarity, ArmorTypeE _AType, int _Defense)
{
	Type_ = ItemTypeE::Armor;

	ID_ = _ID;

	strcpy(Name_, _Name);
	strcpy(IconFilePath_, _IconFilePath);

	Rarity_ = _Rarity;
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
