/**
 * @file	Source\Game\Item\ArmorItemData.h
 *
 * Declares the ArmorItemData class.
 */
#pragma once

#include"IItemData.h"

/**
 * An ArmorItemData.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class ArmorItemData : public IItemData
{
public:

	/** Values that represent ArmorItem types. */
	enum ArmorItemTypeE
	{
		Helm = 1,	//!< “ª
		Armor,		//!< “·
		Arm,		//!< ˜r
		Greaves,	//!< ‹r
	};

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	ArmorItemData();

	/**
	 * Constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/05
	 *
	 * @param	_ID			 	The identifier.
	 * @param	_Name		 	The name.
	 * @param	_IconFilePath	Full pathname of the icon file.
	 * @param	_AType		 	The type.
	 * @param	_Defense	 	The defense.
	 */
	ArmorItemData(int _ID, char* _Name, char* _IconFilePath, ArmorItemTypeE _AType,int _Defense);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ArmorItemData();

	ArmorItemTypeE GetArmorType()
	{
		return AType;
	}

private:

	/** Type of the ArmorItem. */
	ArmorItemTypeE AType;
	/** –hŒä—Í. */
	int Defense = 0;
};