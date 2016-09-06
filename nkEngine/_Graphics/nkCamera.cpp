#include"nkEngine/nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{
	CCamera::CCamera():
		m_vNormalizePosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_vTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_vUp(D3DXVECTOR3(0.0f,1.0f,0.0f)),
		m_Distance(10),
		m_Fovy(D3DXToRadian(45.0f)),
		m_Aspect(0.0f),
		m_Near(0.1f),
		m_Far(1000.0f),
		m_ePerson(EPerson::third)
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

		//m_vPosition = m_vNormalizePosition * m_Distance + m_vTarget;

		if (m_ePerson == EPerson::third)
		{
			D3DXMatrixLookAtLH(&m_mView, &m_vPosition, &m_vTarget, &m_vUp);
		}
		else if (m_ePerson == EPerson::fast)
		{
			D3DXMatrixLookAtLH(&m_mView, &m_vTarget, &m_vPosition, &m_vUp);
		}

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
		D3DXVec3TransformCoord(&m_vNormalizePosition, &m_vNormalizePosition, &tmp);
		//m_vPosition = m_vNormalizePosition * m_Distance + m_vTarget;
	}
	void CCamera::SpinVertically(float rot)
	{

		D3DXQUATERNION qua;
		D3DXMATRIX tmp;
		D3DXVECTOR3 nor = m_vNormalizePosition;
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_vNormalizePosition.z, 0, m_vNormalizePosition.x), rot);
		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&m_vNormalizePosition, &m_vNormalizePosition, &tmp);
		if (m_vNormalizePosition.y >= 0.9 || m_vNormalizePosition.y <= -0.9)
		{
			m_vNormalizePosition = nor;
		}
		//m_vPosition = m_vNormalizePosition * m_Distance + m_vTarget;
	}
}