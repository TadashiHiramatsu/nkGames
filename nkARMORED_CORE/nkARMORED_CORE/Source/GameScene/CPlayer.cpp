#include"stdafx.h"
#include"CPlayer.h"
#include"CGameCamera.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Init()
{
	m_model.Init("White.x");
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
}

void CPlayer::Update()
{
	m_model.Update();
}

void CPlayer::Render()
{
	//Ç≠ÇªèdÇ¢
	m_model.Draw();
}

void CPlayer::Release()
{
	m_model.Release();
}
