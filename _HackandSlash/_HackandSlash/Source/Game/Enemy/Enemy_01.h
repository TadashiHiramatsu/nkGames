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
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< ����
		Waiting = 0,	//!< �ҋ@
		Walk,			//!< ����
		Run,			//!< ����
		Attack_01,		//!< �U���P
		Hit,			//!< �_���[�W
		Death,			//!< ��
		AnimationNum,	//!< �A�j���[�V�����̐�
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
	 * @param animCode		  �Đ�����A�j���[�V�����R�[�h.
	 * @param time ��Ԏ���.
	 */
	void PlayAnimation(AnimationCodeE animCode, float time)
	{
		//���݂̃A�j���[�V�����ł͂Ȃ�
		if (Animation_.GetNowAnimationNo() != (int)animCode)
		{
			Animation_.PlayAnimation((int)animCode, time);
		}

	}
	/**
	 * ���݂̃A�j���[�V�����Ɋ֌W�Ȃ��ݒ肷��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode	�Đ�����A�j���[�V�����R�[�h.
	 * @param time		��Ԏ���.
	 */
	void PlayAnimationAbs(AnimationCodeE animCode, float time)
	{
		Animation_.PlayAnimation((int)animCode, time);
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



};