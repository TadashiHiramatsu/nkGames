#include"stdafx.h"
#include"DropItemManager.h"

#include"../GameCamera.h"

#include"../Item/InventoryManager.h"

/** ������. */
void DropItemManager::Start()
{
	DropItemList_.clear();

	PickUpDistance_ = 0.3;

	AButtonSprite_.Load("Image/AButton.png");
	AButtonSprite_.Start();
	AButtonSprite_.SetTransform(&AButtonTransform_);
	AButtonSprite_.SetCamera(g_MainCamera->GetCamera());
	AButtonTransform_.Scale_ = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

}

/** �X�V. */
void DropItemManager::Update()
{
	//�h���b�v�A�C�e�����X�g�̃C�e���[�^���擾
	auto it = DropItemList_.begin();

	while (it != DropItemList_.end())
	{
		//�X�V
		(*it)->Update();
		it++;
	}

	DropItemList_.sort(DropItem::Comp);

	it = DropItemList_.begin();

	if (it != DropItemList_.end())
	{
		//�擾�ł��鋗���ɃA�C�e�������݂��Ă���
		if ((*it)->GettoPlayerLength() <= PickUpDistance_)
		{
			isGetItem_ = true;
			D3DXVECTOR3 pos = (*it)->Transform_.Position_;
			AButtonTransform_.Position_ = pos + D3DXVECTOR3(0, 0.2f, 0);
			AButtonTransform_.BillboardUpdate(g_MainCamera->GetCamera()->GetRotationMatrix());
		}
		else
		{
			isGetItem_ = false;
		}

		if (isGetItem_ && XInput().IsTrigger(ButtonE::ButtonA))
		{
			InventoryManager().SetItem((*it)->GetEquipmentItem());
			DropItemList_.erase(it);
			isGetItem_ = false;
		}
	}
}

/** �`��. */
void DropItemManager::Render()
{
	for (auto it : DropItemList_)
	{
		it->Render();
	}

	if (isGetItem_)
	{
		AButtonSprite_.Render();
	}
}

/** �����A�C�e�����h���b�v�A�C�e���ɂ��ă��X�g�ɓo�^����. */
void DropItemManager::SetDropItem(EquipmentItem * item, D3DXVECTOR3 & pos)
{
	
	//�h���b�v�A�C�e���̃|�C���^���쐬
	DropItem* dropitem = new DropItem();
	
	dropitem->Start(item, pos, Player_);

	//���X�g�ɐݒ�
	DropItemList_.push_back(dropitem);

}
