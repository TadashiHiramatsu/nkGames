/**
 * @file Source\Game\AnimationEvent\AnimationEventController.h
 *
 * �A�j���[�V�����C�x���g�R���g���[���N���X�̒�`.
 */
#pragma once

#include"AnimationEventMacro.h"

/** �A�j���[�V�����C�x���g�̍ő吔. */
const int ANIMATION_EVENT_MAX = 32;

/** �A�j���[�V�����C�x���g�̎��. */
enum AnimationEventTypeE
{
	Invalid = -1,					//!< ����
	EmitDamageToEnemyCollision,		//!< �G�ɑ΂��ă_���[�W��^����R���W����
	EmitDamageToPlayerCollision,	//!< �v���C���[�Ƀ_���[�W��^����R���W����
};

/**
 * �A�j���[�V�����C�x���g�\����.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct AnimationEventS
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	AnimationEventS()
	{
	}
	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param type    The type.
	 * @param time    The time.
	 * @param fArg0   The argument 0.
	 * @param fArg1   The first f argument.
	 * @param fArg2   The second f argument.
	 * @param fArg3   The third f argument.
	 * @param iArg0   Zero-based index of the argument 0.
	 * @param iArg1   Zero-based index of the argument 1.
	 * @param iArg2   Zero-based index of the argument 2.
	 * @param iArg3   Zero-based index of the argument 3.
	 * @param strArg0 The argument 0.
	 * @param strArg1 The first string argument.
	 * @param strArg2 The second string argument.
	 * @param strArg3 The third string argument.
	 * @param vArg0   The argument 0.
	 * @param vArg1   The first v argument.
	 * @param vArg2   The second v argument.
	 * @param vArg3   The third v argument.
	 */
	AnimationEventS(
		AnimationEventTypeE type,
		float time,
		float fArg0, float fArg1, float fArg2, float fArg3,
		int iArg0, int iArg1, int iArg2, int iArg3,
		const char* strArg0, const char* strArg1, const char* strArg2, const char* strArg3,
		D3DXVECTOR3 vArg0, D3DXVECTOR3 vArg1, D3DXVECTOR3 vArg2, D3DXVECTOR3 vArg3)
	{
		EventType_ = type;
		Time_ = time;
		fArg_[0] = fArg0;
		fArg_[1] = fArg1;
		fArg_[2] = fArg2;
		fArg_[3] = fArg3;

		iArg_[0] = iArg0;
		iArg_[1] = iArg1;
		iArg_[2] = iArg2;
		iArg_[3] = iArg3;

		strArg_[0] = strArg0;
		strArg_[1] = strArg1;
		strArg_[2] = strArg2;
		strArg_[3] = strArg3;

		vArg_[0] = vArg0;
		vArg_[1] = vArg1;
		vArg_[2] = vArg2;
		vArg_[3] = vArg3;
	}

public:

	/** �C�x���g�̃^�C�v. */
	AnimationEventTypeE EventType_;
	/** �C�x���g���������鎞�ԁB�Y������A�j���[�V�������Đ�����Čo�߂������ԁB. */
	float Time_;
	/** ���������_�^�̈���. */
	float fArg_[4];
	/** �����^�̈���. */
	int iArg_[4];
	/** ������̈���. */
	const char* strArg_[4];
	/** �x�N�g���^�̈���. */
	D3DXVECTOR3 vArg_[4];

};

/**
 * �A�j���[�V�����O���[�v.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct AnimationEventGroupS
{
public:

	/** The event [animation event max]. */
	AnimationEventS Event_[ANIMATION_EVENT_MAX];

};

/**
 * �A�j���[�V�����C�x���g�R���g���[��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class AnimationEventController
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	AnimationEventController();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~AnimationEventController();

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
	void Init(ModelRender* model, Animation* anim, AnimationEventGroupS* eventGroupTbl, int tblSize);

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update();

private:

	/**
	 * �A�j���[�V�����C�x���g�̔���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param event The event.
	 */
	void InvokeAnimationEvent(const AnimationEventS& event);

private:

	/**
	 * �A�j���[�V�����C�x���g�e�[�u��.
	 * �C�x���g�������������̃t���O������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct AnimationEventGroupTableS
	{

		/** �A�j���[�V�����C�x���g�O���[�v. */
		AnimationEventGroupS EventGroup_;
		/** �C�x���g�̔����t���O. */
		bool isInvokes_[ANIMATION_EVENT_MAX];

	};
	/** �C�x���g�e�[�u��. */
	vector<AnimationEventGroupTableS> EventGroupTableList_;

	/** 1�t���[���O�̃A�j���[�V�����ԍ�. */
	int AnimNoLastFrame_ = -1;
	/** �A�j���[�V����. */
	Animation* Animation_ = nullptr;
	/** �X�L�����f��. */
	ModelRender* ModelRender_ = nullptr;
	/** 1�t���[���O�̃A�j���[�V�����^�C��. */
	float LastFrameAnimTime_ = 0.0f;
	/** �������ł������ǂ����̃t���O. */
	bool isInited_ = false;

};