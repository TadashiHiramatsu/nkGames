#include"stdafx.h"
#include"CRightArm.h"

CRightArm::CRightArm()
{
}

CRightArm::~CRightArm()
{
}

void CRightArm::Init()
{
	m_model.Init("prototype_2_RightArm.X", NULL);
	m_model.SetTransform(&m_trans);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	//m_trans.SetPosition(D3DXVECTOR3(0,10,0));
}

void CRightArm::Update()
{
	//m_trans.AddPosition(D3DXVECTOR3(0.01f, 0, 0));
	m_model.Update();
}

void CRightArm::Render()
{
	m_model.Render();
}

void CRightArm::Release()
{
	m_model.Release();
}
