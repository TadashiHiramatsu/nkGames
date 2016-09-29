#include"stdafx.h"
#include"CACModelRender.h"

CACModelRender::CACModelRender():
	m_mParent(nullptr)
{
}

CACModelRender::~CACModelRender()
{
}

void CACModelRender::Update()
{
	if (m_isShadowCaster && Shadow().isEnable()) {
		//シャドウキャスター。
		Shadow().Entry(this);
	}

	D3DXMATRIX mPosition, mScale;

	D3DXMatrixTranslation(&mPosition, m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);
	D3DXMatrixRotationQuaternion(&m_mRotation, &m_Transform->GetRotation());
	D3DXMatrixScaling(&mScale, m_Transform->GetScale().x, m_Transform->GetScale().y, m_Transform->GetScale().z);

	m_mWorld = mScale * m_mRotation * mPosition;

	if (m_mParent != nullptr)
	{
		m_mWorld  = m_mWorld * (*m_mParent);
	}

	D3DXMatrixInverse(&m_mWorldInv, NULL, &m_mWorld);

	if (m_ModelData)
	{
		m_ModelData->UpdateBoneMatrix(m_mWorld);
	}
}
