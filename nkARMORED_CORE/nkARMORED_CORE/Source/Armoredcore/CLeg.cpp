#include"stdafx.h"
#include"CLeg.h"

CLeg::CLeg()
{
}

CLeg::~CLeg()
{
}

void CLeg::Init()
{
	m_model.Init("prototype_2_Leg.X", NULL);
	m_model.SetTransform(&m_trans);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	//m_trans.SetPosition(D3DXVECTOR3(0,10,0));
}

void CLeg::Update()
{
	//m_trans.AddPosition(D3DXVECTOR3(0.01f, 0, 0));
	m_model.Update();
}

void CLeg::Render()
{
	m_model.Render();
}

void CLeg::Release()
{
	m_model.Release();
}
