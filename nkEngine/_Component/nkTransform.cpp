#include"nkEngine/nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	CTransform::CTransform() :
		Position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		Scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
		Rotation(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
	{
	}

	CTransform::~CTransform()
	{
	}

}