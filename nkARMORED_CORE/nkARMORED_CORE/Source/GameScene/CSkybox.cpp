#include"stdafx.h"
#include"CSkybox.h"
#include"CGameCamera.h"

CSkybox::CSkybox()
{

}

CSkybox::~CSkybox()
{

}

void CSkybox::Init()
{
	m_model.Load("Skybox.x", NULL);
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);

	m_model.SetFogParam(enFogFuncHeight, 400.0f,0.0f);
	//m_model.SetFogColor(D3DXVECTOR4(0.25f, 0.05f, 0.05f, 0.0f));

	m_trans.SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_trans.SetScale(D3DXVECTOR3(500.0f, 500.0f, 500.0f));

	m_light.SetAmbientLight(D3DXVECTOR3(1.0f,1.0f,1.0f));
}

void CSkybox::Update()
{
	m_model.Update();
}

void CSkybox::Render()
{
	m_model.Render();
}

void CSkybox::Release()
{

}

