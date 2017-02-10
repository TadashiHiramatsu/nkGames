#pragma once

#include"EquipmentItem.h"
#include"ItemType.h"
#include"../../Game/Item/ArmorItemData.h"

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

	static CInventoryManager& GetInstance()
	{
		static CInventoryManager instance;
		return instance;
	}

	//������
	void Start();

	//�A�C�e���̐ݒ�
	void SetItem(EquipmentItem* item);

	//�A�C�e���̎擾
	EquipmentItem* GetItem(ItemTypeE type, int num);

	int GetItemSize(ItemTypeE type)
	{
		return ItemList[type].size();
	}

	EquipmentItem* ChangeItem(ItemTypeE type,EquipmentItem* item, int num);

private:

	vector<EquipmentItem*> ItemList[ItemTypeE::TypeNum];

};

static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}