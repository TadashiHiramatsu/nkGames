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

	/**
	* �v���C���[�̃|�C���^���擾.
	*/
	const Player* GetPlayer() const
	{
		return Player_;
	}

	/**
	* �v���C���[�̍��W���擾.
	*/
	const Vector3& GetPlayerPosition() const
	{
		return Player_->Transform_.Position_;
	}

	/**
	* �ړ����x��ݒ�.
	*
	* @param speed	�ړ����x(�b).
	*/
	void SetMoveSpeed(float speed)
	{
		MoveSpeed_ = speed;
	}

	/**
	* �ړ����x���擾.
	*
	* @return �ړ����x(�b).
	*/
	float GetMoveSpeed()
	{
		return MoveSpeed_;
	}

protected:

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

	/** �v���C���[�̃|�C���^. */
	const Player* Player_ = nullptr;

	/** �ړ����x. */
	float MoveSpeed_ = 80.0f;
	/** �ړ�����. */
	Vector3 MoveDir_ = Vector3::Zero;


};