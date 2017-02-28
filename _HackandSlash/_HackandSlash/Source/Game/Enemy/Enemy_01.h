/**
 * @file Source\Game\Monster\Monster_01.h
 *
 * �����U��������G�N���X�̒�`.
 */
#pragma once

#include"IEnemy.h"

/**
 * �G�N���X.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class Enemy_01 : public IEnemy
{
public:

	/** �A�j���[�V�����R�[�h. */
	enum AnimationCode
	{
		AnimationInvalid = -1,	//!< ����
		AnimationWaiting = 0,	//!< �ҋ@
		AnimationWalk,			//!< ����
		AnimationRun,			//!< ����
		AnimationAttack_01,		//!< �U���P
		AnimationHit,			//!< �_���[�W
		AnimationDeath,			//!< ��
		AnimationNum,			//!< �A�j���[�V�����̐�
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	Enemy_01()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~Enemy_01()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Render()override;

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Release()override;

	/**
	 * �_���[�W.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Damage()override;

	/**
	 * �A�j���[�V������ύX����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimation(AnimationCode animCode, float interpolateTime)
	{
		//���݂̃A�j���[�V�����ł͂Ȃ�
		if (Animation_.GetNowAnimationNo() != animCode)
		{
			Animation_.PlayAnimation(animCode, interpolateTime);
		}

	}
	/**
	 * ���݂̃A�j���[�V�����Ɋ֌W�Ȃ��ݒ肷��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimationAbs(AnimationCode animCode, float interpolateTime)
	{
		Animation_.PlayAnimation(animCode, interpolateTime);
	}

	/**
	 * �A�j���[�V�����Ǘ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void AnimationControl()override;

private:

	/** �R���W�����I�u�W�F�N�g. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** ���̌`��. */
	unique_ptr<SphereCollider> SphereShape_;

	/** ���ł܂ł̎���(�b). */
	float DisappearanceTime_ = 5.0f;
	/** ���Ŏ��Ԃ̃��[�J���^�C��. */
	float DisappearanceLT_ = 0.0f;

};