/**
 * @file	Source\Game\Item\WeaponItemData.cpp
 *
 * Implements the weapon class.
 */
#include"stdafx.h"
#include"WeaponItemData.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
WeaponItemData::WeaponItemData()
{
	Type_ = ItemTypeE::Weapon;
}

WeaponItemData::WeaponItemData(int id, char * itemname, char * iconfilename, ItemTypeE type, int minlevel, int maxlevel, int probability, int attack)
{
	ID_ = id;

	strcpy(Name_, itemname);
	strcpy(IconFilePath_, iconfilename);

	Type_ = type;

	Attack_ = attack;

	MinLevel_ = minlevel;
	MaxLevel_ = maxlevel;
	Probability_ = probability;
}
