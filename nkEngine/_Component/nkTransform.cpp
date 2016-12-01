#include"nkEngine/nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	Transform::Transform() :
		Parent(nullptr),
		ParentMatrix(nullptr),
		Position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		Scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
		Rotation(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Update()
	{
		D3DXMATRIX mTrans, mScale;

		D3DXMatrixTranslation(&mTrans, Position.x, Position.y, Position.z);
		D3DXMatrixRotationQuaternion(&RotationMatrix, &Rotation);
		D3DXMatrixScaling(&mScale, Scale.x, Scale.y, Scale.z);

		LocalMatrix = mScale * RotationMatrix * mTrans;

		if (ParentMatrix)
		{
			D3DXMatrixMultiply(&WorldMatrix, &LocalMatrix, ParentMatrix);
		}
		else
		{
			WorldMatrix = LocalMatrix;
		}

		D3DXMatrixInverse(&WorldMatrixInv, NULL, &WorldMatrix);
	}
}