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
	 * @param	minlevel	 	最低レベル.
	 * @param	maxlevel	 	最高レベル.
	 * @param	probability	 	ドロップ率.
	 * @param	defense	 		防御力.
	 */
	ArmorItemData(
		int id, 
		const string& itemname, 
		const string& iconfilename,
		ItemTypeE type, 
		int minlevel,
		int maxlevel,
		int probability,
		int defense);

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ArmorItemData()
	{
	}

	/**
	* 表示するパラメーターを取得.
	*/
	int GetParameter() const override
	{
		return Defense_;
	}

private:

	/** 防御力. */
	int Defense_ = 0;

};