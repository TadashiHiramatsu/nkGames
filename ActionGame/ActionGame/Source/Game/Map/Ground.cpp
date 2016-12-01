#include"stdafx.h"
#include"Ground.h"

#include"..\GameCamera.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Start()
{
	Model.Load("Ground.X",nullptr);
	Model.SetTransform(&transform);
	Model.SetLight(&Light);
	Model.SetCamera(g_MainCamera->GetCamera());
	Model.SetShadowCasterFlag(true);
	Model.SetShadowReceiverFlag(true);

	Normal.Load("ground4_Normal.tga");
	Model.SetNormalMap(&Normal);
	Specular.Load("ground4_Specular.tga");
	Model.SetSpecMap(&Specular);

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
	transform.Update();

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
