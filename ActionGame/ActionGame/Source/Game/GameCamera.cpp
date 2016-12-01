#include"stdafx.h"
#include"GameCamera.h"

GameCamera::GameCamera() :
	player(nullptr),
	mViewInv(nullptr)
{
}

GameCamera::~GameCamera()
{

}

void GameCamera::Start()
{
	Camera.SetPosDirection(D3DXVECTOR3(0,0.2f,1.0f));
	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.4f, 0));
	Camera.SetDistance(3.0f);
	Camera.Update();

	mViewInv = &Camera.GetViewInvMatrix();
}

void GameCamera::Update()
{
	static float speed = 0.05f;
	if (Input.GetKeyButton(KeyCode::Up))
	{
		Camera.SpinVertically(-speed);
	}
	if (Input.GetKeyButton(KeyCode::Down))
	{
		Camera.SpinVertically(speed);
	}
	if (Input.GetKeyButton(KeyCode::Left))
	{
		Camera.SpinHorizontally(-speed);
	}
	if (Input.GetKeyButton(KeyCode::Right))
	{
		Camera.SpinHorizontally(speed);
	}
	
	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.4f, 0));
	Camera.Update();
}

