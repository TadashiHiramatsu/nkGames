/**
* �����A�C�e���N���X�̒�`.
*/
#pragma once

#include"ItemData\IItemData.h"

/**
* �����A�C�e���N���X.
*/
class EquipmentItem
{
public:

	/**
	* �R���X�g���N�^.
	*/
	EquipmentItem()
	{
	}

	/**
	* �R���X�g���N�^.
	*/
	EquipmentItem(IItemData* itemdata)
	{
		ItemData_ = itemdata;
	}

	/**
	* �f�X�g���N�^.
	*/
	~EquipmentItem()
	{
	}

	/**
	* �A�C�e���^�C�v�̎擾.
	*/
	ItemTypeE GetItemType() const
	{
		return ItemData_->GetItemType();
	}

	/**
	* �A�C�e���f�[�^�̎擾.
	*/
	IItemData* GetItemData() const
	{
		return ItemData_;
	}

	/**
	* �A�C�R���t�@�C���p�X�̎擾.
	*/
	const string& GetIconFilePath() const
	{
		return ItemData_->GetIconFilePath();
	}

	/**
	* �A�C�e�����̎擾.
	*/
	const string& GetName() const
	{
		return ItemData_->GetName();
	}

	/**
	* ����p�����[�^�̎擾.
	*/
	int GetParameter()
	{
		return ItemData_->GetParameter();
	}

	/**
	* �A�C�e��ID�̎擾.
	*/
	int GetID() const
	{
		return ItemData_->GetID();
	}

private:

	/** �A�C�e���f�[�^. */
	IItemData* ItemData_ = nullptr;

};