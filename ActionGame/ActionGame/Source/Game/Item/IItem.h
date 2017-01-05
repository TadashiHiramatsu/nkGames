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
	enum RarityCode
	{
		Common = 1, //�R�����B�ǂ��ł���ɓ���B
		Magic, //�}�W�b�N
		Rare, //���A�B
		Unique, //���j�[�N
	};

	/** �A�C�e���̃^�C�v. */
	/** �A�C�e��ID�̏�ꌅ�ƈ�v. */
	enum ItemType
	{
		Weapon = 1, //����
		Armor = 2, //�h��
		Other = 3, //���̑�
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

protected:
	/** �A�C�e�������ʂ��邽�߂̃R�[�h. */
	// ��:00000 
	// ��ꌅ:�A�C�e���^�C�v
	// �񌅖�:�T�u�^�C�v
	// ���O��:��ID
	int ID;
	/** �A�C�e���̖��́B�Q�[�����ŕ\���������. */
	const char* Name;
	/** �A�C�R���̃t�@�C���p�X . */
	const char* IconFilePath;
	/** ���A���e�B. */
	RarityCode Rarity;
	/** �A�C�e���^�C�v. */
	ItemType Type;
};