#include"stdafx.h"
#include"CLeftArm.h"

CLeftArm::CLeftArm()
{
}

CLeftArm::~CLeftArm()
{
}

void CLeftArm::Init()
{
	m_model.Init("prototype_2_LeftArm.X", NULL);
	m_model.SetTransform(&m_trans);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	//m_trans.SetPosition(D3DXVECTOR3(0,10,0));
}

void CLeftArm::Update()
{
	//m_trans.AddPosition(D3DXVECTOR3(0.01f, 0, 0));
	m_model.Update();
}

void CLeftArm::Render()
{
	m_model.Render();
}

void CLeftArm::Release()
{
	m_model.Release();
}
