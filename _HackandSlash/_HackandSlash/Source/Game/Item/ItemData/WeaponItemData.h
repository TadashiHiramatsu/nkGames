/**
 * @file	Source\Game\Item\WeaponItemData.h
 *
 * Declares the weapon class.
 */
#pragma once

#include"IItemData.h"

/**
 * A weapon.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class WeaponItemData : public IItemData
{
public:

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	WeaponItemData();

	/**
	* コンストラクタ
	 *
	 * @param	id			 	アイテムID.
	 * @param	itemname		アイテム名.
	 * @param	iconfilename	アイコンファイル名.
	 * @param	type		 	アイテムタイプ.
	 * @param	minlevel	 	最低レベル.
	 * @param	maxlevel	 	最高レベル.
	 * @param	probability	 	ドロップ率.
	 * @param	attack	 		攻撃力.
	 */
	WeaponItemData(
		int id,
		char* itemname,
		char* iconfilename,
		ItemTypeE type,
		int minlevel,
		int maxlevel,
		int probability,
		int attack);


	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~WeaponItemData()
	{
	}

	/**
	* 表示するパラメーターを取得.
	*/
	int GetParameter()override
	{
		return Attack_;
	}

private:

	/** 攻撃力. */
	int Attack_;

};