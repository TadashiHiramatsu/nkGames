/**
 * @file	Source\Game\GameCamera.h
 *
 * �Q�[���J�����N���X�̒�`.
 */
#pragma once

#include"Player\Player.h"

/**
 * �Q�[���J�����N���X.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class GameCamera : public IGameObject
{
public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	GameCamera()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~GameCamera()
	{
	}

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * �J�������擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	Null if it fails, else the camera.
	 */
	const Camera* GetCamera() const
	{
		return &Camera_;
	}

	/**
	 * Sets player pointer.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	pla	If non-null, the pla.
	 */
	void SetPlayer(const Player* pla)
	{
		Player_ = pla;
	}

	/**
	 * �J�����̑O�������擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction forward.
	 */
	const Vector3& GetDirectionForward() const
	{
		Vector3 dirForward;
		dirForward.x = ViewInvMatrix_->m[2][0];
		dirForward.y = 0.0f;		//Y������Ȃ��B
		dirForward.z = ViewInvMatrix_->m[2][2];

		//Y����ł������Ă���̂Ő��K������B
		dirForward.Normalize();
		return dirForward;
	}

	/**
	 * �J�����̉E�������擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction right.
	 */
	const Vector3& GetDirectionRight() const
	{
		Vector3 dirRight;
		dirRight.x = ViewInvMatrix_->m[0][0];
		dirRight.y = 0.0f;		//Y���͂���Ȃ��B
		dirRight.z = ViewInvMatrix_->m[0][2];

		//Y����ł������Ă���̂Ő��K������B
		dirRight.Normalize();
		return dirRight;
	}

private:

	/** �J����. */
	Camera Camera_;
	/** �v���C���[. */
	const Player* Player_ = nullptr;
	/** ����. */
	float Distance_;
	/** �ő勗��. */
	float DistanceMax_;

	/** �r���[�s��̋t�s��. */
	const Matrix* ViewInvMatrix_ = nullptr;

	/** ��]�X�s�[�h.��b�Ԃɉ�]����p�x. */
	float SpinSpeed = 45.0f;

	/** �v���C���[�̏���������钲��. */
	Vector3 PlusPosition_;

	/** �J�����R���W�����N���X. */
	CameraCollision CameraCollision_;

};

/** �O���[�o��. */
extern GameCamera* g_MainCamera;