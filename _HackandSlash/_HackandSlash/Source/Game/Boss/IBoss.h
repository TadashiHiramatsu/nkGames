/**
* �{�X�̊��N���X�̒�`.
*/
#pragma once

#include"../Player/Player.h"

/**
* �{�X�̊��N���X.
* �S�Ẵ{�X�����X�^�[�͂�����p������.
*/
class IBoss : public IGameObject
{
protected:

	/** ��ԃR�[�h. */
	enum class StateCodeE
	{
		Spawn,		//!< �o��.
		Waiting,	//!< �����~�܂�.
		Chase,		//!< �ǂ�����.
		Turn,		//!< �Ȃ���.
		Attack,	//!< �U��.
		Death,		//!< ��.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	IBoss()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~IBoss()
	{
		Release();
	}

	/**
	* ������.
	*/
	virtual void Start()override;

	/**
	* �X�V.
	*/
	virtual void Update()override;

	/**
	* �`��.
	*/
	virtual void Render()override;

	/**
	* ���.
	*/
	virtual void Release()override;

	/**
	* �_���[�W�֐�.
	*/
	virtual void Damage()
	{
	}

	/**
	* �v���C���[�̃|�C���^��ݒ�.
	*/
	void SetPlayer(const Player* p)
	{
		Player_ = p;
	}

protected:

	/**
	* ��ԑJ��.
	*
	* @param nextstate	���̏��.
	*/
	void ChangeState(StateCodeE nextstate)
	{
		State_ = nextstate;
	}
	
	/**
	* �A�j���[�V�����Ǘ�.
	* �p����̃N���X�Ŏ�������.
	*/
	virtual void AnimationControl()
	{
	}

protected:

	/** �X�L�����f���f�[�^�n���h��. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** ���f�������_�[. */
	ModelRender ModelRender_;
	/** �A�j���[�V����. */
	Animation Animation_;

	/** ���a. */
	float Radius_ = 0.5f;
	/** ����. */
	float Height_ = 0.5f;
	/** �L�����N�^�[�R���g���[��. */
	CharacterController CharacterController_;

	/** ���. */
	StateCodeE State_;

	/** �v���C���[�̃|�C���^. */
	const Player* Player_ = nullptr;

};