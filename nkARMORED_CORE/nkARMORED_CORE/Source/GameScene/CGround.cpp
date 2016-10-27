#include"stdafx.h"
#include"CGround.h"
#include"CGameCamera.h"

CGround::CGround()
{

}

CGround::~CGround()
{

}

void CGround::Init()
{
	m_model.Load("Field_02.X",NULL);
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
	m_model.SetShadowReceiverFlag(true);
	m_model.SetShadowCasterFlag(true);
	m_model.SetFogParam(enFogFuncDist, 300.0f, 400.0f);
	//m_model.SetFogColor(D3DXVECTOR4(0.25f, 0.05f, 0.05f,0.0f));

	m_NormalMap.Load("Field_02_Normal.tga");
	m_model.SetNormalMap(&m_NormalMap);

	m_model.Update();
	m_mWorld = m_model.FindBoneWorldMatrix("Plane001");

	//メッシュコライダー作成
	m_MeshCollider.Create(&m_model, m_mWorld);
	//剛体作成
	SRigidBodyInfo rbInfo;
	rbInfo.Collider = &m_MeshCollider;
	rbInfo.Mass = 0.0f;
	m_RigidBody.Create(rbInfo);

	g_Physics.AddRigidBody(&m_RigidBody);
}

void CGround::Update()
{
	m_model.Update();
}

void CGround::Render()
{
	//Engine().GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_model.Render();
	//Engine().GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CGround::Release()
{

}
