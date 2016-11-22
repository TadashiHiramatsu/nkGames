#include"stdafx.h"
#include"IMonster.h"

#include"..\GameCamera.h"

IMonster::IMonster():
	Radius(0.4f),
	Height(0.3f),
	Hp(10),
	Distance(10),
	toPlayerMaxDis(20),
	PlayerAttackDis(0.3f),
	WaitingTime(4),
	LocalTime(0),
	Destination(D3DXVECTOR3(0, 0, 0))
{
}

IMonster::~IMonster()
{
}

void IMonster::Init()
{
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());
}

void IMonster::Update()
{
	Model.Update();
}

void IMonster::Render()
{
	Model.Render();
}

void IMonster::Release()
{
	Model.Release();
}