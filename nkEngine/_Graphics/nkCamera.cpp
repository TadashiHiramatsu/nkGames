#include"nkEngine/nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{
	CCamera::CCamera():
		m_vTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_vPosDirection(D3DXVECTOR3(0.0f, 0.0f, -1.0f)),
		m_vUp(D3DXVECTOR3(0.0f,1.0f,0.0f)),
		m_Distance(1),
		m_Fovy(D3DXToRadian(45.0f)),
		m_Aspect(0.0f),
		m_Near(0.1f),
		m_Far(1200.0f),
		m_LowerLimit(-0.8f),
		m_UpperLimit(0.8f)
	{
		D3DXMatrixIdentity(&m_mView);
		D3DXMatrixIdentity(&m_mProj);
		D3DXMatrixIdentity(&m_mRotation);
		D3DXMatrixIdentity(&m_mRotationInv);
	}

	CCamera::~CCamera()
	{

	}

	void CCamera::Update()
	{
		//プロジェクション行列の計算
		m_Aspect = (float)Engine().GetFrameW() / (float)Engine().GetFrameH();
		D3DXMatrixPerspectiveFovLH(&m_mProj, m_Fovy, m_Aspect, m_Near, m_Far);

		D3DXVec3Normalize(&m_vPosDirection, &m_vPosDirection);
		m_vPosDirection.y = min(m_UpperLimit, m_vPosDirection.y);
		m_vPosDirection.y = max(m_LowerLimit, m_vPosDirection.y);

		m_vPosition = m_vPosDirection * m_Distance + m_vTarget;

		D3DXMatrixLookAtLH(&m_mView, &m_vPosition, &m_vTarget, &m_vUp);

		D3DXMatrixInverse(&m_mViewInv, NULL, &m_mView);
		m_mRotation = m_mViewInv;
		m_mRotation.m[3][0] = 0.0f;
		m_mRotation.m[3][1] = 0.0f;
		m_mRotation.m[3][2] = 0.0f;
		m_mRotation.m[3][3] = 1.0f;
		D3DXMatrixTranspose(&m_mRotationInv, &m_mRotation);
	}
	void CCamera::SpinHorizontally(float rot)
	{
		D3DXMATRIX tmp;
		D3DXMatrixRotationY(&tmp, rot);
		D3DXVec3TransformCoord(&m_vPosDirection, &m_vPosDirection, &tmp);
	}
	void CCamera::SpinVertically(float rot)
	{
		D3DXQUATERNION qua;
		D3DXMATRIX tmp;
		//横方向
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_vPosDirection.z, 0, m_vPosDirection.x), rot);
		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&m_vPosDirection, &m_vPosDirection, &tmp);
	}
}