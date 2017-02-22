/**
 * @file	Source\Game\GameCamera.cpp
 *
 * �Q�[���J�����N���X�̎���.
 */
#include"stdafx.h"
#include"GameCamera.h"

#include"Window\MenuWindow\MenuSystem.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
GameCamera::GameCamera() :
	Player_(nullptr),
	ViewInvMatrix_(nullptr)
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
GameCamera::~GameCamera()
{
}

/**
 * Starts this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Start()
{
	Camera_.SetPosDirection(D3DXVECTOR3(0.0f, 0.2f, -1.0f));
	Camera_.SetTarget(Player_->Transform_.Position_ + D3DXVECTOR3(0, 0.4f, 0));

	Distance_ = 8.0f;
	Camera_.SetDistance(Distance_);
	Camera_.Update();

	ViewInvMatrix_ = &Camera_.GetViewInvMatrix();
}

/**
 * �X�V.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Update()
{
	//�J�����܂킷��[
	
	if (!g_MenuSystem->GetEffectiveness())
	{
		Camera_.SpinHorizontally(XInput().GetRightStick().x * SpinSpeed * Time().DeltaTime());
		Camera_.SpinVertically(XInput().GetRightStick().y * SpinSpeed * Time().DeltaTime() * -1);
	}

	Camera_.SetTarget(Player_->Transform_.Position_ + D3DXVECTOR3(0, 0.6f, 0));
	Camera_.Update();
}