#include"stdafx.h"
#include"Monster_01.h"

#include"..\GameCamera.h"

Monster_01::Monster_01()
{

}

Monster_01::~Monster_01()
{
}

void Monster_01::Init()
{
	Model.Load("Monster_01.X", &Animation);
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());
	Model.SetRimLight(true);

	Transform.Position = D3DXVECTOR3(1, 1, 0);
	DefaultPosition = D3DXVECTOR2(Transform.Position.x, Transform.Position.z);
	
	Animation.PlayAnimation(AnimationWaiting);

	CharacterController.Init(0.4f, 0.3f, Transform.Position);
}

void Monster_01::Update()
{
	D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);

	CharacterController.SetMoveSpeed(move);
	CharacterController.Update();
	Transform.Position = CharacterController.GetPosition();

	Animation.Update(1.0f / 60.0f);
	Model.Update();
}

void Monster_01::Render()
{
	Model.Render();
}

void Monster_01::Release()
{
	Model.Release();
}