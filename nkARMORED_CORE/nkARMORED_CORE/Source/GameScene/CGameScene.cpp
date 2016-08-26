#include"stdafx.h"
#include"CGameScene.h"
#include"CGameCamera.h"

void CGameScene::Init()
{
	g_camera.Init();
	//m_ground.Init();
	//m_p.Init();
}

void CGameScene::Update()
{
	g_camera.Update();
	//m_ground.Update();
	//m_p.Update();
	{
		m_player = new CPlayer();
		m_player->Init();
		m_player->Release();
	}
}

void CGameScene::Render()
{
	//m_p.Render();
	//m_ground.Render();
}

void CGameScene::Release()
{
	//m_ground.Release();
}
