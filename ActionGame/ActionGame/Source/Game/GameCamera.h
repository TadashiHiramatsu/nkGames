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
	GameCamera();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~GameCamera();

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
	Camera* GetCamera()
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
	void SetPlayer(Player* pla)
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
	D3DXVECTOR3& GetDirectionForward()
	{
		D3DXVECTOR3 dirForward;
		dirForward.x = ViewInvMatrix_->m[2][0];
		dirForward.y = 0.0f;		//Y������Ȃ��B
		dirForward.z = ViewInvMatrix_->m[2][2];
		D3DXVec3Normalize(&dirForward, &dirForward);//Y����ł������Ă���̂Ő��K������B
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
	D3DXVECTOR3& GetDirectionRight()
	{
		D3DXVECTOR3 dirRight;
		dirRight.x = ViewInvMatrix_->m[0][0];
		dirRight.y = 0.0f;		//Y���͂���Ȃ��B
		dirRight.z = ViewInvMatrix_->m[0][2];
		D3DXVec3Normalize(&dirRight, &dirRight);//Y����ł������Ă���̂Ő��K������B
		return dirRight;
	}

private:

	/** �J����. */
	Camera Camera_;
	/** �v���C���[. */
	Player* Player_;
	/** ����. */
	float Distance_;
	/** The view inverse matrix. */
	const D3DXMATRIX* ViewInvMatrix_;
};

/** �O���[�o��. */
extern GameCamera* g_MainCamera;