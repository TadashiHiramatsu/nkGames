#include"stdafx.h"
#include"CHead.h"

CHead::CHead()
{
}

CHead::~CHead()
{
}

void CHead::Init()
{
	m_model.Init("prototype_2_Head.X", NULL);
	m_model.SetTransform(&m_trans);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	//m_trans.SetPosition(D3DXVECTOR3(0,10,0));
}

void CHead::Update()
{
	//m_trans.AddPosition(D3DXVECTOR3(0.01f, 0, 0));
	m_model.Update();
}

void CHead::Render()
{
	m_model.Render();
}

void CHead::Release()
{
	m_model.Release();
}
