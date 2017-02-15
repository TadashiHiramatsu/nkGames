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
 * @param	_ID			 	The identifier.
 * @param	_Name		 	The name.
 * @param	_IconFilePath	Full pathname of the icon file.
 * @param	type		 	The type.
 * @param	_Defense	 	The defense.
 */
ArmorItemData::ArmorItemData(int _ID, char * _Name, char * _IconFilePath, ItemTypeE type, int _Defense)
{
	ID_ = _ID;

	strcpy(Name_, _Name);
	strcpy(IconFilePath_, _IconFilePath);

	Type_ = type;

	Defense_ = _Defense;
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
ArmorItemData::~ArmorItemData()
{
}
