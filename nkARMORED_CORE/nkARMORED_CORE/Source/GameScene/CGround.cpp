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
	m_model.Load("Field_02.X",NULL);
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
	m_model.SetShadowReceiverFlag(true);
	m_model.SetShadowCasterFlag(true);
	m_model.SetFogParam(enFogFuncDist, 300.0f, 400.0f);
	//m_model.SetFogColor(D3DXVECTOR4(0.25f, 0.05f, 0.05f,0.0f));

	m_NormalMap.Load("Field_02_Normal.tga");
	m_model.SetNormalMap(&m_NormalMap);

}

void CGround::Update()
{
	m_model.Update();
}

void CGround::Render()
{
	m_model.Render();
}

void CGround::Release()
{

}
