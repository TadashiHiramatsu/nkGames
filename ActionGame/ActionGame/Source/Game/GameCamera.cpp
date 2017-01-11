/**
 * @file	Source\Game\GameCamera.cpp
 *
 * ゲームカメラクラスの実装.
 */
#include"stdafx.h"
#include"GameCamera.h"

/**
 * コンストラクタ.
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
 * デストラクタ.
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
	Camera_.SetPosDirection(D3DXVECTOR3(0.0f, 1.0f, 1.0f));
	Camera_.SetTarget(Player_->Transform_.Position_ + D3DXVECTOR3(0, 0.4f, 0));

	Distance_ = 5.0f;
	Camera_.SetDistance(Distance_);
	Camera_.Update();

	ViewInvMatrix_ = &Camera_.GetViewInvMatrix();
}

/**
 * 更新.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Update()
{
	if (Input().GetKeyButton(KeyCode::Up))
	{
		Camera_.SpinVertically(-0.03f);
	}
	if (Input().GetKeyButton(KeyCode::Down))
	{
		Camera_.SpinVertically(0.03f);
	}
	if (Input().GetKeyButton(KeyCode::Left))
	{
		Camera_.SpinHorizontally(-0.03f);
	}
	if (Input().GetKeyButton(KeyCode::Right))
	{
		Camera_.SpinHorizontally(0.03f);
	}

	Camera_.SetTarget(Player_->Transform_.Position_ + D3DXVECTOR3(0, 0.6f, 0));
	Camera_.Update();
}