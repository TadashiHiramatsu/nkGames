#include"stdafx.h"
#include"Ground.h"

#include"..\GameCamera.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Init()
{
	Model.Load("Ground.X",nullptr);
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());

	Update();

	mWorld = Model.FindBoneWorldMatrix("Plane001");
	MeshCollider.Create(&Model, mWorld);
	SRigidBodyInfo rbInfo;
	rbInfo.Collider = &MeshCollider;
	rbInfo.Mass = 0.0f;
	RigidBody.Create(rbInfo);
	RigidBody.GetBody()->setUserIndex(ECollisionAttr::CollisionAttr_Ground);
	Physics().AddRigidBody(&RigidBody);
}

void Ground::Update()
{
	Model.Update();
}

void Ground::Render()
{
	Model.Render();
}

void Ground::Release()
{
	Model.Release();
}
