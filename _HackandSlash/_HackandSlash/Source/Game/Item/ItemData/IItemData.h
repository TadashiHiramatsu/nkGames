/**
 * @file	Source\Game\Item\IItem.h
 *
 * Declares the IItem interface.
 */
#pragma once

#include"ItemType.h"

/**
 * �A�C�e���̊��N���X 
 * �A�C�e�������\�[�X�N���X�ň������� 
 * ID�Ŏ��ʂ���.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class IItemData
{
public:

	static const int TypeID = 1000;

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	IItemData()
	{
	}


	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	virtual ~IItemData() 
	{
	}

	/**
	 * ID���擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return The identifier.
	 */
	int GetID()
	{
		return ID_;
	}

	/**
	* �A�C�e�����̎擾.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @return Null if it fails, else the name.
	*/
	const char* GetName()
	{
		return Name_;
	}

	/**
	 * �A�C�R���t�@�C���p�X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return Null if it fails, else the icon file path.
	 */
	const char* GetIconFilePath()
	{
		return IconFilePath_;
	}

	/**
	 * �A�C�e���^�C�v�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return The item type.
	 */
	ItemTypeE GetItemType()
	{
		return Type_;
	}

	/**
	* �e��p�����[�^���擾����.
	*/
	virtual int GetParameter()
	{
		return -1;
	}

	/**
	* �Œ჌�x�����擾.
	*/
	int GetMinLevel()
	{
		return MinLevel_;
	}

	/**
	* �ō����x�����擾.
	*/
	int GetMaxLevel()
	{
		return MaxLevel_;
	}

	/**
	* �h���b�v�����擾.
	*/
	int GetProbability()
	{
		return Probability_;
	}

protected:

	/**   
	* �A�C�e�������ʂ��邽�߂̃R�[�h. 
	* ��:1001 
	* ��1��:�A�C�e���^�C�v
	* ��3��:��ID
	*/
	int ID_ = 0;
	/** �A�C�e���̖��́B�Q�[�����ŕ\���������. */
	char Name_[64];
	/** �A�C�R���̃t�@�C���p�X . */
	char IconFilePath_[64];
	/** �A�C�e���^�C�v. */
	ItemTypeE Type_;

	/** �Œ჌�x��. */
	int MinLevel_ = 0;
	/** �ō����x��. */
	int MaxLevel_ = 100;
	/** �h���b�v�m��. */
	int Probability_ = 100;

};