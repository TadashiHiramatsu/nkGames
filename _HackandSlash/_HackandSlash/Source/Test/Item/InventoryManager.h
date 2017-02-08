#pragma once

#include"../../Game/Item/IItem.h"

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


public:

	//�R���X�g���N�^
	CInventoryManager()
	{
	}

	//�f�X�g���N�^
	~CInventoryManager()
	{
	}

	//������
	void Start();

	//�A�C�e���̐ݒ�
	void SetItem(IItem* item, ItemTypeE type);

	//�A�C�e���̎擾
	IItem* GetItem(ItemTypeE type, int num);

private:

	vector<IItem*> ItemList[ItemTypeE::TypeNum];

};