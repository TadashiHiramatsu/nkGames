#pragma once

#include"DropItem.h"
#include"../Player/Player.h"

/**
* �h���b�v�A�C�e���̃��X�g���Ǘ�����
*/
class DropItemManager : public IGameObject
{
public:

	struct DataS
	{
		/** �A�C�e���f�[�^. */
		IItemData* ItemData_;
		/** �h���b�v��. */
		int Probability_;
	};

public:
	
	//�R���X�g���N�^
	DropItemManager()
	{
	}

	//�f�X�g���N�^
	~DropItemManager()
	{
	}

	/** 
	* ������. 
	*/
	void Start()override;

	/**
	* �X�V. 
	*/
	void Update()override;

	/** 
	* �`��. 
	*/
	void Render()override;

	/** 
	* �����A�C�e�����h���b�v�A�C�e���ɂ��ă��X�g�ɓo�^����. 
	*
	* @param level	�G�̃��x��.
	* @param pos	�h���b�v������W.
	**/
	void SetDropItem(int level, const Vector3& pos);

	/** �v���C���[�̃|�C���^��ݒ�. */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

	bool GetisGetItem() const
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
