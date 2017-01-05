/**
 * @file	Source\Game\Item\Armor.h
 *
 * Declares the armor class.
 */
#pragma once

#include"IItem.h"

/**
 * An armor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class Armor : public IItem
{
public:

	/** Values that represent armor types. */
	enum ArmorType
	{
		Head = 1,	// ì™
		Shoulders,	// å®
		Torso,		// ì∑
		Wrists,		// òr
		Hands,		// éË
		Waist,		// çò
		Legs,		// ãr
		Feet,		// åC
	};

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	Armor();

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
	Armor(int _ID, const char* _Name, const char* _IconFilePath, RarityCode _Rarity, ArmorType _AType,int _Defense);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~Armor();
private:

	/** Type of the armor. */
	ArmorType AType;
	/** ñhå‰óÕ. */
	int Defense = 0;
};