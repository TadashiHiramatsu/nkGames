#include"stdafx.h"
#include"CBoxCollider.h"

CBoxCollider::CBoxCollider():
	m_Shape(nullptr)
{
}

CBoxCollider::~CBoxCollider()
{
	SAFE_DELETE(m_Shape);
}

void CBoxCollider::Create(const D3DXVECTOR3 & size)
{
	m_Shape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
}
