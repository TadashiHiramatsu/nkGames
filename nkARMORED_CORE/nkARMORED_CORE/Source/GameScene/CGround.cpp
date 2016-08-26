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
	m_model.Init("Ground.x");
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);

	m_trans.SetPosition(D3DXVECTOR3(0.0f, -50.0f, 0.0f));
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
