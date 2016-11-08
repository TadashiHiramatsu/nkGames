#include"nkEngine/nkstdafx.h"
#include"nkSphereCollider.h"

namespace nkEngine
{
	CSphereCollider::CSphereCollider() :
		m_Shape(nullptr)
	{
	}

	CSphereCollider::~CSphereCollider()
	{
		SAFE_DELETE(m_Shape);
	}

	void CSphereCollider::Create(const float _radius)
	{
		m_Shape = new btSphereShape(_radius);
	}
}