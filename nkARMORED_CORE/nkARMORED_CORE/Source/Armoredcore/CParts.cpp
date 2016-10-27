#include"stdafx.h"
#include"CParts.h"

CParts::CParts():
	m_isBreak(false)
{

}

CParts::~CParts()
{

}

void CParts::Init()
{
	m_ACModel.SetTransform(&m_Transform);
	m_ACModel.SetShadowCasterFlag(true);
	m_ACModel.SetShadowReceiverFlag(true);
}

void CParts::Update()
{
	if (m_isBreak)
	{
		const btVector3& rPos = m_RigidBody.GetBody()->getWorldTransform().getOrigin();
		D3DXVECTOR3 pos(rPos.x(), rPos.y(), rPos.z());
		const btQuaternion& rRot = m_RigidBody.GetBody()->getWorldTransform().getRotation();
		D3DXQUATERNION rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
		m_Transform.SetPosition(pos);
		m_Transform.SetRotation(rot);
	}

	m_ACModel.Update();
}

void CParts::Render()
{
	m_ACModel.Render();
}

void CParts::Release()
{
	m_ACModel.Release();
}

void CParts::LoadModel(const char* filepass)
{
	m_ACModel.Load(filepass, &m_Animation);
}

void CParts::InitRigidBody()
{
	m_isBreak = true;

	m_ACModel.Update();
	//m_mWorld = m_ACModel.FindBoneWorldMatrix("Hip");

	//メッシュコライダー作成
	m_MeshCollider.Create(&m_ACModel, m_mWorld);

	//剛体作成
	SRigidBodyInfo rbInfo;
	rbInfo.Collider = &m_MeshCollider;
	rbInfo.Mass = 10.0f;
	m_RigidBody.Create(rbInfo);

	g_Physics.AddRigidBody(&m_RigidBody);
}
