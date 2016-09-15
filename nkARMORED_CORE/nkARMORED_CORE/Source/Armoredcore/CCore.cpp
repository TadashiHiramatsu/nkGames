#include"stdafx.h"
#include"CCore.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

void CCore::Init()
{
	m_model.Init("prototype_2_Core.X", NULL);
	m_model.SetTransform(&m_trans);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	//m_trans.SetPosition(D3DXVECTOR3(0,10,0));
}

void CCore::Update()
{
	//m_trans.AddPosition(D3DXVECTOR3(0.01f, 0, 0));
	m_model.Update();
}

void CCore::Render()
{
	m_model.Render();
}

void CCore::Release()
{
	m_model.Release();
}
