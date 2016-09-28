#include"stdafx.h"
#include"CRigidBody.h"
#include"CCollider.h"

CRigidBody::CRigidBody():
	m_RigidBody(nullptr),
	m_MotionState(nullptr)
{
}

CRigidBody::~CRigidBody()
{
	Release();
}

void CRigidBody::Release()
{
	SAFE_DELETE(m_RigidBody);
	SAFE_DELETE(m_MotionState);
}

void CRigidBody::Create(SRigidBodyInfo & rbInfo)
{
	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.Position.x, rbInfo.Position.y, rbInfo.Position.z));
	transform.setRotation(btQuaternion(rbInfo.Rotation.x, rbInfo.Rotation.y, rbInfo.Rotation.z, rbInfo.Rotation.w));
	m_MotionState = new btDefaultMotionState;
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.Mass, m_MotionState, rbInfo.Collider->GetBody(), btVector3(0, 0, 0));
	//„‘Ì‚ğì¬B
	m_RigidBody = new btRigidBody(btRbInfo);
}
