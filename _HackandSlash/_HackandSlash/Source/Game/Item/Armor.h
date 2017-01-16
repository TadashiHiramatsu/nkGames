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
	enum ArmorTypeE
	{
		Head = 1,	//!< “ª
		Shoulders,	//!< Œ¨
		Torso,		//!< “·
		Wrists,		//!< ˜r
		Hands,		//!< Žè
		Waist,		//!< ˜
		Legs,		//!< ‹r
		Feet,		//!< ŒC
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
	Armor(int _ID, char* _Name, char* _IconFilePath, RarityCodeE _Rarity, ArmorTypeE _AType,int _Defense);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~Armor();
private:

	/** Type of the armor. */
	ArmorTypeE AType;
	/** –hŒä—Í. */
	int Defense = 0;
};