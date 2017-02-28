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
	 * @param	id			 	アイテムID.
	 * @param	itemname		アイテム名.
	 * @param	iconfilename	アイコンファイル名.
	 * @param	type		 	アイテムタイプ.
	 * @param	defense	 		防御力.
	 * @param	minlevel	 	最低レベル.
	 * @param	maxlevel	 	最高レベル.
	 * @param	probability	 	ドロップ率.
	 */
	ArmorItemData(
		int id, 
		char* itemname, 
		char* iconfilename, 
		ItemTypeE type, 
		int defense,
		int minlevel,
		int maxlevel,
		int probability);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ArmorItemData()
	{
	}

	int GetParameter()override
	{
		return Defense_;
	}

private:

	/** 防御力. */
	int Defense_ = 0;

};