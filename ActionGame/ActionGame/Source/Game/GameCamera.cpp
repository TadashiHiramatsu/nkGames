/**
 * @file	Source\Game\GameCamera.cpp
 *
 * Implements the game camera class.
 */
#include"stdafx.h"
#include"GameCamera.h"

/**
 * Default constructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
GameCamera::GameCamera() :
	player(nullptr),
	mViewInv(nullptr)
{
}

/**
 * Destructor.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
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
	Camera.SetPosDirection(D3DXVECTOR3(0.0f, 1.0f, 1.0f));
	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.4f, 0));

	distance = 5.0f;
	Camera.SetDistance(distance);
	Camera.Update();

	mViewInv = &Camera.GetViewInvMatrix();
}

/**
 * Updates this object.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
void GameCamera::Update()
{
	if (Input.GetKeyButton(KeyCode::Up))
	{
		Camera.SpinVertically(-0.03f);
	}
	if (Input.GetKeyButton(KeyCode::Down))
	{
		Camera.SpinVertically(0.03f);
	}
	if (Input.GetKeyButton(KeyCode::Left))
	{
		Camera.SpinHorizontally(-0.03f);
	}
	if (Input.GetKeyButton(KeyCode::Right))
	{
		Camera.SpinHorizontally(0.03f);
	}

	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.6f, 0));
	Camera.Update();
}