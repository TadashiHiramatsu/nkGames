#include"stdafx.h"
#include"AnimationEventController.h"
#include"CollisionWorld.h"

AnimationEventController::AnimationEventController()
{
}

AnimationEventController::~AnimationEventController()
{
}

void AnimationEventController::Init(CModelRender * _skinModel, CAnimation * _anim, AnimationEventGroup * _eventGroupTbl, int _tblSize)
{
	if (_eventGroupTbl == NULL)
	{
		return;
	}
	this->skinModel = _skinModel;
	this->animation = _anim;
	eventGroupTbl.resize(_tblSize);
	for (int i = 0; i < _tblSize; i++)
	{
		eventGroupTbl[i].eventGroup = _eventGroupTbl[i];
		memset(eventGroupTbl[i].invokeFlags, 0, sizeof(eventGroupTbl[i].invokeFlags));
	}
	isInited = true;
}

void AnimationEventController::Update()
{
	if (!isInited)
	{
		//�������ł��ĂȂ�
		return;
	}

	int currentAnimNo = animation->GetNowAnimationNo();
	float animTime = animation->GetLocalAnimationTime();

	if (animNoLastFrame != -1 && animNoLastFrame != currentAnimNo)
	{
		//�A�j���[�V�������؂�ւ����
		//�O�̃A�j���[�V�����̃C�x���g�����t���O������������
		memset(eventGroupTbl[animNoLastFrame].invokeFlags, 0, sizeof(eventGroupTbl[animNoLastFrame].invokeFlags));
	}
	else if (animTime < lastFrameAnimTime)
	{
		//�O�̃t���[�������A�j���[�V�������Ԃ��������Ȃ���(���[�v����)
		//�c���Ă�C�x���g��S�����������Ă��珉����
		AnimationEventGroupEx& eventGroupEx = eventGroupTbl[currentAnimNo];
		for (int i = 0; 
			eventGroupEx.eventGroup.event[i].eventType != eAnimationEventType_Invalid;
			i++)
		{
			if (eventGroupEx.invokeFlags[i] == false)
			{
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//�����ς�
				eventGroupEx.invokeFlags[i] = true;
			}
		}
		memset(eventGroupTbl[animNoLastFrame].invokeFlags, 0, sizeof(eventGroupTbl[animNoLastFrame].invokeFlags));
	}
	lastFrameAnimTime = animTime;

	AnimationEventGroupEx& eventGroupEx = eventGroupTbl[currentAnimNo];

	for (int i = 0;
		eventGroupEx.eventGroup.event[i].eventType != eAnimationEventType_Invalid;
		i++)
	{
		if (eventGroupEx.invokeFlags[i] == false)
		{
			//�܂��C�x���g���������Ă��Ȃ�
			if (eventGroupEx.eventGroup.event[i].time <= animTime)
			{
				//�C�x���g�������鎞�Ԃ��o�߂���
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//�����ς�
				eventGroupEx.invokeFlags[i] = true;
			}
		}
	}
	animNoLastFrame = currentAnimNo;
}

void AnimationEventController::InvokeAnimationEvent(const AnimationEvent & _event)
{
	switch (_event.eventType)
	{
	case eAnimationEventType_EmitDamageToEnemyCollision:
		//�G�Ƀ_���[�W��^����R���W��������
	{
		D3DXMATRIX* bone = skinModel->FindBoneWorldMatrix(_event.strArg[0]);
		D3DXVECTOR3 pos = _event.vArg[0];
		if (bone != NULL)
		{
			//�o�^
			D3DXVec3TransformCoord(&pos, &pos, bone);
			g_CollisionWorld->Add(_event.fArg[1], pos, _event.fArg[0], _event.iArg[0], CollisionWorld::enDamageToEnemy, _event.iArg[1]);
		}
	}
	break;
	case eAnimationEventType_EmitDamageToPlayerCollision:
		//�v���C���[�Ƀ_���[�W��^����R���W��������.
	{
		D3DXMATRIX* bone = skinModel->FindBoneWorldMatrix(_event.strArg[0]);
		D3DXVECTOR3 pos = _event.vArg[0];
		if (bone != NULL)
		{
			//�o�^
			D3DXVec3TransformCoord(&pos, &pos, bone);
			g_CollisionWorld->Add(_event.fArg[1], pos, _event.fArg[0], _event.iArg[0], CollisionWorld::enDamageToPlayer, _event.iArg[1]);
		}
	}
	break;
	default:
		break;
	}
}