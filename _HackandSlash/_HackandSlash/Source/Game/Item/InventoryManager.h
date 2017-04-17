#pragma once

#include"EquipmentItem.h"
#include"ItemData\ArmorItemData.h"

/**
* �E�����A�C�e�����Ǘ�����N���X.
* �V�[���N���X���Ǘ�����.
*/
class CInventoryManager
{

private:

	//�R���X�g���N�^
	CInventoryManager()
	{
	}

	//�f�X�g���N�^
	~CInventoryManager()
	{
	}

public:

	/**
	* �C���X�^���X���擾.
	*/
	static CInventoryManager& GetInstance()
	{
		static CInventoryManager instance;
		return instance;
	}

	/**
	* ������.
	*/
	void Start();

	/**
	* �A�C�e���̐ݒ�.
	*/
	void SetItem(EquipmentItem* item);

	/**
	* �A�C�e���̎擾.
	*/
	EquipmentItem* GetItem(ItemTypeE type, int num);

	/**
	* �A�C�e�����������擾.
	*/
	int GetItemSize(ItemTypeE type)
	{
		return ItemList_[type].size();
	}

	/**
	* �A�C�e����ύX.
	*/
	EquipmentItem* ChangeItem(ItemTypeE type, EquipmentItem* item, int num);

private:

	/**
	* �ǂݎ��.
	*/
	void Continue();

public:

	/**
	* ��������.
	*/
	void Save();

private:

	/** �A�C�e�����X�g. */
	vector<EquipmentItem*> ItemList_[ItemTypeE::TypeNum];

};

/**
* �C���x���g���}�l�[�W���̎擾.
*/
static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}