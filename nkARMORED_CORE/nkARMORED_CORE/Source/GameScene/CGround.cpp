#include"stdafx.h"
#include"CGround.h"
#include"CGameCamera.h"

CGround::CGround()
{

}

CGround::~CGround()
{

}

void CGround::Init()
{
	m_model.Init("Court.x");
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
	m_model.SetShadowReceiverFlag(true);

	m_trans.SetPosition(D3DXVECTOR3(0.0f, -0.05f, 0.0f));
	m_trans.SetScale(D3DXVECTOR3(10, 0, 10));
}

void CGround::Update()
{
	m_model.Update();
}

void CGround::Render()
{
	m_model.Draw();
}

void CGround::Release()
{

}
