#include"stdafx.h"
#include"DropItemManager.h"

#include"../GameCamera.h"

#include"../Item/InventoryManager.h"
#include"../Item/ItemDataResource.h"

/** ������. */
void DropItemManager::Start()
{
	DropItemList_.clear();

	PickUpDistance_ = 2.0f;

	AButtonSprite_.Load("Image/AButton.png");
	AButtonSprite_.Start();
	AButtonSprite_.SetTransform(&AButtonTransform_);
	AButtonSprite_.SetCamera(g_MainCamera->GetCamera());
	AButtonTransform_.Scale_ = Vector3(0.1f, 0.1f, 1.0f);

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
			Vector3 pos = (*it)->Transform_.Position_;
			AButtonTransform_.Position_.Add(pos, Vector3(0, 0.5f, 0));
			AButtonTransform_.BillboardUpdate(g_MainCamera->GetCamera()->GetRotationMatrix());
		}
		else
		{
			isGetItem_ = false;
		}

		if (isGetItem_ && XInput().IsTrigger(ButtonE::A))
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

void DropItemManager::SetDropItem(int level,const Vector3 & pos)
{
	//���̓G�����Ƃ��A�C�e��
	vector<DataS*> ItemList;

	//���ۂ̃h���b�v�l?
	int probability = 0;

	//���݂���A�C�e��.
	auto& ItemMap = ItemDataResource().GetItemMap();
	for (auto it : ItemMap)
	{
		if (it.second->GetMinLevel() <= level && level <= it.second->GetMaxLevel())
		{
			DataS* data = new DataS();

			//�A�C�e���f�[�^��ݒ�.
			data->ItemData_ = it.second;

			//�h���b�v�������Z
			probability += it.second->GetProbability();

			//�h���b�v����ݒ�
			data->Probability_ = probability;


			ItemList.push_back(data);
		}
	}

	int p = Random().Range(0, max(999999, probability));

	EquipmentItem* item = nullptr;

	for(auto it : ItemList)
	{
		if (p < it->Probability_)
		{
			item = new EquipmentItem(it->ItemData_);
			break;
		}
	}

	if (item != nullptr)
	{

		//�h���b�v�A�C�e���̃|�C���^���쐬
		DropItem* dropitem = new DropItem();
		dropitem->Start(item, pos, Player_);

		//���X�g�ɐݒ�
		DropItemList_.push_back(dropitem);
	}

	ItemList.clear();
}
