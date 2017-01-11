/**
 * @file Source\Game\AnimationEvent\AnimationEventController.cpp
 *
 * �A�j���[�V�����C�x���g�R���g���[���N���X�̒�`.
 */
#include"stdafx.h"
#include"AnimationEventController.h"
#include"CollisionWorld.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
AnimationEventController::AnimationEventController()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
AnimationEventController::~AnimationEventController()
{
}

/**
* ������.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param [in,out] model		 ���f�������_�N���X.
* @param [in,out] anim			 �A�j���[�V�����N���X.
* @param [in,out] eventGroupTbl �C�x���g�O���[�v.
* @param 		   tblSize		 Size of the table.
*/
void AnimationEventController::Init(ModelRender* model, Animation* anim, AnimationEventGroupS* eventGroupTbl, int tblSize)
{
	//�C�x���g�O���[�v���Ȃ���
	if (eventGroupTbl == NULL)
	{
		return;
	}

	ModelRender_ = model;
	Animation_ = anim;

	//�C�x���g�O���[�v�̏�����
	EventGroupTableList_.resize(tblSize);
	for (int i = 0; i < tblSize; i++)
	{
		EventGroupTableList_[i].EventGroup_ = eventGroupTbl[i];
		memset(EventGroupTableList_[i].isInvokes_, 0, sizeof(EventGroupTableList_[i].isInvokes_));
	}

	//�������ł���
	isInited_ = true;

}

void AnimationEventController::Update()
{

	if (!isInited_)
	{
		//�������ł��ĂȂ�
		return;
	}

	//���ݍĐ����̃A�j���[�V�����ԍ����擾
	int currentAnimNo = Animation_->GetNowAnimationNo();

	//���[�J���A�j���[�V�����^�C�����擾
	float animTime = Animation_->GetLocalAnimationTime();

	//1�t���[���̃A�j���[�V�����^�C����-1���͌��݂���Ȃ�
	if (AnimNoLastFrame_ != -1 && AnimNoLastFrame_ != currentAnimNo)
	{
		//�A�j���[�V�������؂�ւ����
		//�O�̃A�j���[�V�����̃C�x���g�����t���O������������
		memset(EventGroupTableList_[AnimNoLastFrame_].isInvokes_, 0, sizeof(EventGroupTableList_[AnimNoLastFrame_].isInvokes_));
	}
	else if (animTime < LastFrameAnimTime_)
	{
		//�O�̃t���[�������A�j���[�V�������Ԃ��������Ȃ���(���[�v����)
		//�c���Ă�C�x���g��S�����������Ă��珉����
		
		//���ݍĐ����̃A�j���[�V�����̃A�j���[�V�����C�x���g���擾
		AnimationEventGroupTableS& eventGroupTable = EventGroupTableList_[currentAnimNo];

		//�C�x���g�^�C�v�������ɂȂ�܂�
		for (int i = 0; eventGroupTable.EventGroup_.Event_[i].EventType_ != Invalid;i++)
		{
			//�����������Ƃ��Ȃ����
			if (eventGroupTable.isInvokes_[i] == false)
			{
				InvokeAnimationEvent(eventGroupTable.EventGroup_.Event_[i]);
				//�����ς݂ɕύX
				eventGroupTable.isInvokes_[i] = true;
			}
		}

		//�t���O�����ׂď�����
		memset(EventGroupTableList_[AnimNoLastFrame_].isInvokes_, 0, sizeof(EventGroupTableList_[AnimNoLastFrame_].isInvokes_));
	}

	//1�t���[���O�̃A�j���[�V�����^�C�����R�s�[
	LastFrameAnimTime_ = animTime;

	//���ݍĐ����̃A�j���[�V�����̃A�j���[�V�����C�x���g���擾
	AnimationEventGroupTableS& eventGroupTable = EventGroupTableList_[currentAnimNo];

	//�C�x���g�^�C�v�������ɂȂ�܂ōX�V
	for (int i = 0;eventGroupTable.EventGroup_.Event_[i].EventType_ != Invalid;i++)
	{
		//�������������Ƃ��Ȃ����
		if (eventGroupTable.isInvokes_[i] == false)
		{
			//�܂��C�x���g���������Ă��Ȃ�
			if (eventGroupTable.EventGroup_.Event_[i].Time_ <= animTime)
			{
				//�C�x���g�������鎞�Ԃ��o�߂���
				InvokeAnimationEvent(eventGroupTable.EventGroup_.Event_[i]);
				//�����ς݂ɕύX
				eventGroupTable.isInvokes_[i] = true;

			}
			else
			{
				//���Ԍo�߂��Ƃɓo�^���Ă���ꍇ��
				//���̏���������Ă��������邱�Ƃ��Ȃ�����Break���Ă������̂ł́H
				break;
			}

		}

	}

	//�A�j���[�V�����g���b�N�ԍ��̍X�V
	AnimNoLastFrame_ = currentAnimNo;

}

/**
* �A�j���[�V�����C�x���g�̔���.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param event The event.
*/
void AnimationEventController::InvokeAnimationEvent(const AnimationEventS& event)
{
	//�^�C�v���ɈႤ������
	switch (event.EventType_)
	{
	case EmitDamageToEnemyCollision:
		//�G�Ƀ_���[�W��^����R���W��������
	{
		//�{�[�����擾 ���̓���d���ˁH
		D3DXMATRIX* bone = ModelRender_->FindBoneWorldMatrix(event.strArg_[0]);

		//�|�W�V�����̈ړ����擾
		D3DXVECTOR3 pos = event.vArg_[0];

		//�{�[�������݂��Ă����
		if (bone != NULL)
		{

			//�|�W�V�����̈ړ������v�Z
			D3DXVec3TransformCoord(&pos, &pos, bone);

			//�R���W�������[���h�ɓo�^
			g_CollisionWorld->Add(event.fArg_[1], pos, event.fArg_[0], event.iArg_[0], CollisionWorld::DamageToEnemy, event.iArg_[1]);
		
		}
	}
	break;

	case EmitDamageToPlayerCollision:
		//�v���C���[�Ƀ_���[�W��^����R���W��������.
	{
		//�{�[�����擾 ���̓���d���ˁH
		D3DXMATRIX* bone = ModelRender_->FindBoneWorldMatrix(event.strArg_[0]);
		
		//�|�W�V�����̈ړ������擾
		D3DXVECTOR3 pos = event.vArg_[0];

		//�{�[�������݂��Ă����
		if (bone != NULL)
		{

			//�|�W�V�����̈ړ������v�Z
			D3DXVec3TransformCoord(&pos, &pos, bone);

			//�R���W�������[���h�ɓo�^
			g_CollisionWorld->Add(event.fArg_[1], pos, event.fArg_[0], event.iArg_[0], CollisionWorld::DamageToPlayer, event.iArg_[1]);
		}
	}
	break;

	default:
		break;
	}

}