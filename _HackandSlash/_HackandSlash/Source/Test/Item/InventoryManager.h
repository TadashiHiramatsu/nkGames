#pragma once

#include"../../Game/Item/IItemData.h"

#include"../../Game/Item/ArmorItemData.h"

/**
* �E�����A�C�e�����Ǘ�����N���X.
* �V�[���N���X���Ǘ�����.
*/
class CInventoryManager
{

public:

	enum ItemTypeE
	{
		Sword,		//!< ��
		Shield,		//!< ��
		Helm,		//!< ��
		Armor,		//!< ��
		Arm,		//!< �r
		Greaves,	//!< �r
		Accessory,	//!< �A�N�Z�T���[
		TypeNum,    //!< ��
	};


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
	void SetItem(IItemData* item);

	//�A�C�e���̎擾
	IItemData* GetItem(ItemTypeE type, int num);

	int GetItemSize(ItemTypeE type)
	{
		return ItemList[type].size();
	}

private:

	void SetArmor(ArmorItemData* item);

private:

	vector<IItemData*> ItemList[ItemTypeE::TypeNum];

};

static CInventoryManager& InventoryManager()
{
	return CInventoryManager::GetInstance();
}