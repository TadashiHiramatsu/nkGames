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
	 * @param	id			 	�A�C�e��ID.
	 * @param	itemname		�A�C�e����.
	 * @param	iconfilename	�A�C�R���t�@�C����.
	 * @param	type		 	�A�C�e���^�C�v.
	 * @param	defense	 		�h���.
	 * @param	minlevel	 	�Œ჌�x��.
	 * @param	maxlevel	 	�ō����x��.
	 * @param	probability	 	�h���b�v��.
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

	/** �h���. */
	int Defense_ = 0;

};