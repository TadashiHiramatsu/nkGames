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
	* �R���X�g���N�^
	 *
	 * @param	id			 	�A�C�e��ID.
	 * @param	itemname		�A�C�e����.
	 * @param	iconfilename	�A�C�R���t�@�C����.
	 * @param	type		 	�A�C�e���^�C�v.
	 * @param	minlevel	 	�Œ჌�x��.
	 * @param	maxlevel	 	�ō����x��.
	 * @param	probability	 	�h���b�v��.
	 * @param	attack	 		�U����.
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
	* �\������p�����[�^�[���擾.
	*/
	int GetParameter()override
	{
		return Attack_;
	}

private:

	/** �U����. */
	int Attack_;

};