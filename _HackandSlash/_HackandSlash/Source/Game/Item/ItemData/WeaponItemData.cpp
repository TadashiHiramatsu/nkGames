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

WeaponItemData::WeaponItemData(int id, const string& itemname, const string& iconfilename, ItemTypeE type, int minlevel, int maxlevel, int probability, int attack) :
	IItemData(id, itemname, iconfilename, type, minlevel, maxlevel, probability)
{
	Attack_ = attack;
}
