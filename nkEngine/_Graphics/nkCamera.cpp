#include"nkEngine/nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{
	CCamera::CCamera():
		m_vNormalizeTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_vTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_vUp(D3DXVECTOR3(0.0f,1.0f,0.0f)),
		m_Distance(10),
		m_Fovy(D3DXToRadian(45.0f)),
		m_Aspect(0.0f),
		m_Near(1.0f),
		m_Far(1000.0f)
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

		//ビュー行列の計算
		m_vPosition = m_vNormalizeTarget * m_Distance + m_vTarget;

		D3DXVECTOR3 zaxis;//注視点から視点への方向（正規化）
		D3DXVec3Normalize(&zaxis, &D3DXVECTOR3(m_vTarget - m_vPosition));
		D3DXVECTOR3 xaxis;//その方向と上方向の外積（正規化）
		D3DXVec3Normalize(&xaxis, D3DXVec3Cross(&xaxis, &m_vUp, &zaxis));
		D3DXVECTOR3 yaxis;//以上二つの外積
		D3DXVec3Cross(&yaxis, &zaxis, &xaxis);
		m_mView = D3DXMATRIX(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			-D3DXVec3Dot(&xaxis, &m_vPosition), -D3DXVec3Dot(&yaxis, &m_vPosition), -D3DXVec3Dot(&zaxis, &m_vPosition), 1);

		D3DXMATRIX mViewInv;
		D3DXMatrixIdentity(&mViewInv);
		D3DXMatrixInverse(&mViewInv, NULL, &m_mView);
		m_mRotation = mViewInv;
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
		D3DXVec3TransformCoord(&m_vNormalizeTarget, &m_vNormalizeTarget, &tmp);
	}
	void CCamera::SpinVertically(float rot)
	{
		D3DXQUATERNION qua;
		D3DXMATRIX tmp;
		D3DXQuaternionRotationAxis(&qua, &D3DXVECTOR3(-m_vNormalizeTarget.z, 0, m_vNormalizeTarget.x), rot);
		D3DXMatrixRotationQuaternion(&tmp, &qua);
		D3DXVec3TransformCoord(&m_vNormalizeTarget, &m_vNormalizeTarget, &tmp);
	}
}