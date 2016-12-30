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
	Camera.SetPosDirection(D3DXVECTOR3(0.0f, 1.0f, 1.0f));
	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.4f, 0));

	distance = 5.0f;
	Camera.SetDistance(distance);
	Camera.Update();

	mViewInv = &Camera.GetViewInvMatrix();
}

void GameCamera::Update()
{
	Camera.SetTarget(player->transform.Position + D3DXVECTOR3(0, 0.6f, 0));
	Camera.Update();
}

