#pragma once

#include"AnimationEventMacro.h"

const int ANIMATION_EVENT_MAX = 32;

//�A�j���[�V�����C�x���g�̎��
enum EAnimationEventType
{
	eAnimationEventType_EmitDamageToEnemyCollision, //�G�ɑ΂��ă_���[�W��^����R���W����
	eAnimationEventType_EmitDamageToPlayerCollision, //�v���C���[�Ƀ_���[�W��^����R���W����
	eAnimationEventType_Invalid = 0xffffffff,
};

//�A�j���[�V�����C�x���g
struct AnimationEvent
{
public:
	AnimationEvent() {}
	AnimationEvent(
		EAnimationEventType type,
		float time,
		float fArg0, float fArg1, float fArg2, float fArg3,
		int iArg0, int iArg1, int iArg2, int iArg3,
		const char* strArg0, const char* strArg1, const char* strArg2, const char* strArg3,
		D3DXVECTOR3 vArg0, D3DXVECTOR3 vArg1, D3DXVECTOR3 vArg2, D3DXVECTOR3 vArg3)
	{
		this->eventType = type;
		this->time = time;
		fArg[0] = fArg0;
		fArg[1] = fArg1;
		fArg[2] = fArg2;
		fArg[3] = fArg3;

		iArg[0] = iArg0;
		iArg[1] = iArg1;
		iArg[2] = iArg2;
		iArg[3] = iArg3;

		strArg[0] = strArg0;
		strArg[1] = strArg1;
		strArg[2] = strArg2;
		strArg[3] = strArg3;

		vArg[0] = vArg0;
		vArg[1] = vArg1;
		vArg[2] = vArg2;
		vArg[3] = vArg3;
	}

public:
	EAnimationEventType eventType; //�C�x���g�̃^�C�v
	float time; //�C�x���g���������鎞�ԁB�Y������A�j���[�V�������Đ�����Čo�߂������ԁB
	float fArg[4]; //���������_�^�̈���
	int iArg[4]; //�����^�̈���
	const char* strArg[4]; //������̈���
	D3DXVECTOR3 vArg[4]; //�x�N�g���^�̈���
};

//�A�j���[�V�����O���[�v
struct AnimationEventGroup
{
	AnimationEvent event[ANIMATION_EVENT_MAX];
};

//�A�j���[�V�����C�x���g�R���g���[��
class AnimationEventController
{
public:
	//�R���X�g���N�^
	AnimationEventController();

	//�f�X�g���N�^
	~AnimationEventController();
	
	//������
	void Init(CModelRender* _skinModel, CAnimation* _anim, AnimationEventGroup* _eventGroupTbl, int _tblSize);

	//�X�V
	void Update();

private:

	//�A�j���[�V�����C�x���g�̔���
	void InvokeAnimationEvent(const AnimationEvent& _event);

private:
	struct AnimationEventGroupEx
	{
		AnimationEventGroup eventGroup;
		bool invokeFlags[ANIMATION_EVENT_MAX]; //�C�x���g�̔����t���O
	};
	//1�t���[���O�̃A�j���[�V�����ԍ�
	int animNoLastFrame = -1;
	//�A�j���[�V����
	CAnimation* animation = nullptr;
	//�C�x���g�e�[�u��
	vector<AnimationEventGroupEx> eventGroupTbl;
	//�X�L�����f��
	CModelRender* skinModel = nullptr;
	//1�t���[���O�̃A�j���[�V�����^�C��
	float lastFrameAnimTime = 0.0f;
	//�������ł������ǂ����̃t���O
	bool isInited = false;
};