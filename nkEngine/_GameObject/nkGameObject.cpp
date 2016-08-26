#include"nkEngine/nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{
	CGameObject::CGameObject():
		m_Priority(100),
		m_Active(true),
		m_Death(false)
	{}
	CGameObject::~CGameObject()
	{
	}
}