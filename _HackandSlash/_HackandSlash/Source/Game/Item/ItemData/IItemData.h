/**
 * �A�C�e���̊��N���X�̒�`.
 */
#pragma once

#include"ItemType.h"

/**
 * �A�C�e���̊��N���X.
 * �A�C�e�������\�[�X�N���X�ň�������.
 * ID�Ŏ��ʂ���.
 */
class IItemData
{
public:

	static const int TypeID = 1000;

public:

	/**
	* �R���X�g���N�^.
	*/
	IItemData()
	{
	}

	/**
	 * �R���X�g���N�^.
	 *
	 * @param	id			 	�A�C�e��ID.
	 * @param	itemname		�A�C�e����.
	 * @param	iconfilename	�A�C�R���t�@�C����.
	 * @param	type		 	�A�C�e���^�C�v.
	 * @param	minlevel	 	�Œ჌�x��.
	 * @param	maxlevel	 	�ō����x��.
	 * @param	probability	 	�h���b�v��.
	 */
	IItemData(
		int id,
		const string& itemname,
		const string& iconfilename,
		ItemTypeE type,
		int minlevel,
		int maxlevel,
		int probability);

	/**
	 * �f�X�g���N�^.
	 */
	virtual ~IItemData() 
	{
	}

	/**
	 * ID���擾.
	 *
	 * @return The identifier.
	 */
	int GetID() const
	{
		return ItemID_;
	}

	/**
	* �A�C�e�����̎擾.
	*
	* @return Null if it fails, else the name.
	*/
	const string& GetName() const
	{
		return Name_;
	}

	/**
	 * �A�C�R���t�@�C���p�X�̎擾.
	 *
	 * @return Null if it fails, else the icon file path.
	 */
	const string& GetIconFilePath() const
	{
		return IconFilePath_;
	}

	/**
	 * �A�C�e���^�C�v�̎擾.
	 *
	 * @return The item type.
	 */
	ItemTypeE GetItemType() const
	{
		return Type_;
	}

	/**
	* �e��p�����[�^���擾����.
	*/
	virtual int GetParameter() const
	{
		return -1;
	}

	/**
	* �Œ჌�x�����擾.
	*/
	int GetMinLevel() const
	{
		return MinLevel_;
	}

	/**
	* �ō����x�����擾.
	*/
	int GetMaxLevel() const
	{
		return MaxLevel_;
	}

	/**
	* �h���b�v�����擾.
	*/
	int GetProbability() const
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
	int ItemID_ = 0;
	/** �A�C�e���̖��́B�Q�[�����ŕ\���������. */
	string Name_ = "";
	/** �A�C�R���̃t�@�C���p�X . */
	string IconFilePath_ = "";
	/** �A�C�e���^�C�v. */
	ItemTypeE Type_ = ItemTypeE::Weapon;

	/** �Œ჌�x��. */
	int MinLevel_ = 0;
	/** �ō����x��. */
	int MaxLevel_ = 100;
	/** �h���b�v�m��. */
	int Probability_ = 100;
};