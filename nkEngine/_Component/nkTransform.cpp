#include"nkEngine/nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{
	CTransform::CTransform():
		m_position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
		m_rotation(D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f))
	{
	}
	CTransform::~CTransform()
	{
	}
}