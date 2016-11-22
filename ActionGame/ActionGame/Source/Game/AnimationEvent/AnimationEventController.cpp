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
		//初期化できてない
		return;
	}

	int currentAnimNo = animation->GetNowAnimationNo();
	float animTime = animation->GetLocalAnimationTime();

	if (animNoLastFrame != -1 && animNoLastFrame != currentAnimNo)
	{
		//アニメーションが切り替わった
		//前のアニメーションのイベント発生フラグを初期化する
		memset(eventGroupTbl[animNoLastFrame].invokeFlags, 0, sizeof(eventGroupTbl[animNoLastFrame].invokeFlags));
	}
	else if (animTime < lastFrameAnimTime)
	{
		//前のフレームよりもアニメーション時間が小さくなった(ループした)
		//残ってるイベントを全部発生させてから初期化
		AnimationEventGroupEx& eventGroupEx = eventGroupTbl[currentAnimNo];
		for (int i = 0; 
			eventGroupEx.eventGroup.event[i].eventType != eAnimationEventType_Invalid;
			i++)
		{
			if (eventGroupEx.invokeFlags[i] == false)
			{
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//発生済み
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
			//まだイベントが発生していない
			if (eventGroupEx.eventGroup.event[i].time <= animTime)
			{
				//イベント発生する時間が経過した
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//発生済み
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
		//敵にダメージを与えるコリジョン発生
	{
		D3DXMATRIX* bone = skinModel->FindBoneWorldMatrix(_event.strArg[0]);
		D3DXVECTOR3 pos = _event.vArg[0];
		if (bone != NULL)
		{
			//登録
			D3DXVec3TransformCoord(&pos, &pos, bone);
			g_CollisionWorld->Add(_event.fArg[1], pos, _event.fArg[0], _event.iArg[0], CollisionWorld::enDamageToEnemy, _event.iArg[1]);
		}
	}
	break;
	case eAnimationEventType_EmitDamageToPlayerCollision:
		//プレイヤーにダメージを与えるコリジョン発生.
	{
		D3DXMATRIX* bone = skinModel->FindBoneWorldMatrix(_event.strArg[0]);
		D3DXVECTOR3 pos = _event.vArg[0];
		if (bone != NULL)
		{
			//登録
			D3DXVec3TransformCoord(&pos, &pos, bone);
			g_CollisionWorld->Add(_event.fArg[1], pos, _event.fArg[0], _event.iArg[0], CollisionWorld::enDamageToPlayer, _event.iArg[1]);
		}
	}
	break;
	default:
		break;
	}
}