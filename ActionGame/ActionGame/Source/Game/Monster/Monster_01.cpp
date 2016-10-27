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

	Transform.Position = D3DXVECTOR3(1, 1, 0);

	Animation.PlayAnimation(0);

}

void Monster_01::Update()
{
	Animation.Update(1.0f / 120.0f);
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