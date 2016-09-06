#include"stdafx.h"
#include"CObject.h"
#include"CGameCamera.h"

CObject::CObject()
{

}

CObject::~CObject()
{

}

void CObject::Init()
{
	m_model.Init("nature.x",NULL);
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
	m_model.SetShadowReceiverFlag(true);
	m_model.SetFogParam(enFogFuncDist, 80.0f, 160.0f);


	m_trans.SetPosition(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
}

void CObject::Update()
{
	m_model.Update();
}

void CObject::Render()
{
	m_model.Draw();
}

void CObject::Release()
{

}
