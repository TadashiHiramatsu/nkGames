#include"nkEngine/nkstdafx.h"
#include"nkCapsuleCollider.h"

namespace nkEngine
{
	CCapsuleCollider::CCapsuleCollider():
		m_Shape(nullptr)
	{
	}
	CCapsuleCollider::~CCapsuleCollider()
	{
		delete m_Shape;
	}
	
}