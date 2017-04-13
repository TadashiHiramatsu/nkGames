/**
* �E�H�[���b�N�̃{�X�N���X�̒�`.
*/
#pragma once

#include"../IBoss.h"

#include"HFSM\IWarlockState.h"
class IWarlockState;

/**
* �E�H�[���b�N�̃{�X�N���X.
* �l�Ԃ𗠐؂舫���ƌ_�񂵂����@�g��.
*/
class Boss_Warlock : public IBoss
{
public:

	/** �A�j���[�V�����R�[�h. */
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< ����.
		Idol = 0,		//!< �ҋ@.
		Walk,			//!< ���s.
	};

	/** ��ԃR�[�h. */
	enum class StateCodeE
	{
		Invalid = -1,	//!< ����.
		Waiting = 0,	//!< �ҋ@.
		Combat,			//!< �퓬.
		Death,			//!< ��.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	Boss_Warlock()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~Boss_Warlock()
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
	* ���.
	*/
	void Release()override;

	/**
	* �A�j���[�V������ύX.
	*
	* @param animcode	�Đ�����A�j���[�V�����R�[�h.
	* @param time		��Ԏ���.
	*/
	void PlayAnimation(AnimationCodeE animcode, float time)
	{
		//���ݍĐ����Ă���A�j���[�V�����łȂ����.
		if (Animation_.GetNowAnimationNo() != (int)animcode)
		{
			//�ύX.
			Animation_.PlayAnimation((int)animcode, time);
		}
	}

	/**
	* ��ԑJ��.
	*
	* @param nextstate	���̏��.
	*/
	void ChangeState(StateCodeE nextstate);

private:

	/**
	* �_���[�W�֐�.
	*/
	void Damage()override;

	/**
	* �A�j���[�V�����Ǘ�.
	*/
	void AnimationControl()override;

	/** 
	* HFSM�̏�����.
	*/
	void InitHFSM();

private:

	/** ���. */
	StateCodeE State_ = StateCodeE::Invalid;

	/** ��ԃ��X�g. */
	vector<unique_ptr<IWarlockState>> StateList_;

};