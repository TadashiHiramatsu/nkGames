/**
 * @file	Source\Game\Item\IItem.cpp
 *
 * Declares the IItem interface.
 */
#include"stdafx.h"
#include"IItem.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
IItem::IItem():
	Type_(ItemTypeE::Other)
{
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
IItem::~IItem()
{
}
