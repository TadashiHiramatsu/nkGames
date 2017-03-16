/**
* �{�X_01�N���X�̒�`.
*/
#pragma once

#include"IBoss.h"

/**
* �{�X_01�N���X.
*/
class Boss_01 : public IBoss
{
private:

	/** �A�j���[�V�����R�[�h. */
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< ����.
		Waiting,		//!< �ҋ@.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	Boss_01()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~Boss_01()
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

private:

	/**
	* �_���[�W�֐�.
	*/
	void Damage()override;

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
	* �A�j���[�V�����Ǘ�.
	*/
	void AnimationControl()override;

private:



};