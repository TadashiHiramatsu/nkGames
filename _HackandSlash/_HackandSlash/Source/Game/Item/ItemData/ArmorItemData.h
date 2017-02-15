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
	 * @param	type		 	The type.
	 * @param	_Defense	 	The defense.
	 */
	ArmorItemData(int _ID, char* _Name, char* _IconFilePath, ItemTypeE type,int _Defense);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ArmorItemData();

	int GetParameter()override
	{
		return Defense_;
	}

private:

	/** –hŒä—Í. */
	int Defense_ = 0;

};