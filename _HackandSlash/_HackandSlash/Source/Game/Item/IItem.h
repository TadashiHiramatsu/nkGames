/**
 * @file	Source\Game\Item\IItem.h
 *
 * Declares the IItem interface.
 */
#pragma once

/**
 * �A�C�e���̊��N���X 
 * �A�C�e�������\�[�X�N���X�ň������� 
 * ID�Ŏ��ʂ���.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class IItem
{
public:

	static const int TypeID = 10000;
	static const int SubTypeID = 1000;

	/** ���A���e�B�B�������ꂾ��. */
	enum RarityCodeE
	{
		Common = 1,		//!< �R�����B�ǂ��ł���ɓ���B
		Magic,			//!< �}�W�b�N
		Rare,			//!< ���A�B
		Unique,			//!< ���j�[�N
	};

	/** �A�C�e���̃^�C�v. */
	/** �A�C�e��ID�̏�ꌅ�ƈ�v. */
	enum ItemTypeE
	{
		Weapon = 1,		//!< ����
		Armor = 2,		//!< �h��
		Other = 3,		//!< ���̑�
	};

public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	IItem();


	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	virtual ~IItem();

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
	 * ���A���e�B�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @return The rarity.
	 */
	RarityCodeE GetRarity()
	{
		return Rarity_;
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

protected:

	/**   
	* �A�C�e�������ʂ��邽�߂̃R�[�h. 
	* ��:00000 
	* ��ꌅ:�A�C�e���^�C�v
	* �񌅖�:�T�u�^�C�v
	* ���O��:��ID
	*/
	int ID_ = 0;
	/** �A�C�e���̖��́B�Q�[�����ŕ\���������. */
	char Name_[64];
	/** �A�C�R���̃t�@�C���p�X . */
	char IconFilePath_[64];
	/** ���A���e�B. */
	RarityCodeE Rarity_;
	/** �A�C�e���^�C�v. */
	ItemTypeE Type_;

};