#pragma once

#include"../Item/EquipmentItem.h"

/**
* �v���C���[���Z�b�g���Ă��鑕��.
*/
class PlayerEquipment
{
public:

	/**
	* �R���X�g���N�^
	*/
	PlayerEquipment();

	/**
	* �f�X�g���N�^
	*/
	~PlayerEquipment()
	{
	}

	/**
	* �A�C�e�����擾
	*
	* @param type	�A�C�e���^�C�v.
	*
	* @return �A�C�e��.
	*/
	EquipmentItem* GetEquipmentItem(ItemTypeE type)
	{
		return EquipmentItem_[type];
	}

	/**
	* �A�C�e����ݒ�.
	* 
	* @param item	�A�C�e��.
	*/
	void SetEquipmentItem(EquipmentItem* item)
	{
		EquipmentItem_[item->GetItemType()] = item;
	}

	/**
	* �A�C�e�����ݒ肳��Ă��邩�̃t���O��Ԃ��܂�.
	*
	* @param type	�A�C�e���^�C�v.
	*
	* @return true or false.
	*/
	bool GetIsItemSet(ItemTypeE type) const
	{
		if (EquipmentItem_[type] != nullptr)
		{
			return true;
		}
		return false;
	}

private:

	/** �ݒ�A�C�e��. */
	EquipmentItem* EquipmentItem_[ItemTypeE::TypeNum];

};