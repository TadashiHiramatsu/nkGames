#pragma once

#include"DropItem.h"
#include"../Player/Player.h"

/**
* �h���b�v�A�C�e���̃��X�g���Ǘ�����
*/
class DropItemManager : public IGameObject
{
public:
	
	//�R���X�g���N�^
	DropItemManager()
	{
	}

	//�f�X�g���N�^
	~DropItemManager()
	{
	}

	/** ������. */
	void Start()override;

	/** �X�V. */
	void Update()override;

	/** �`��. */
	void Render()override;

	/** �����A�C�e�����h���b�v�A�C�e���ɂ��ă��X�g�ɓo�^����. */
	void SetDropItem(EquipmentItem* item, D3DXVECTOR3& pos);

	/** �v���C���[�̃|�C���^��ݒ�. */
	void SetPlayer(Player* player)
	{
		Player_ = player;
	}

	bool GetisGetItem()
	{
		return isGetItem_;
	}

private:

	/** �Ǘ����X�g. */
	list<DropItem*> DropItemList_;

	/** �A�C�e�����E���鋗��*/
	float PickUpDistance_ = 0;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

	/** �擾�ł���A�C�e�������݂���t���O*/
	bool isGetItem_ = false;

	/** �{�^��. */
	Sprite AButtonSprite_;
	Transform AButtonTransform_;

};

extern DropItemManager* g_DropItemManager;
