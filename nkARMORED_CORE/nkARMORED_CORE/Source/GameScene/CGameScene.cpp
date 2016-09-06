#include"stdafx.h"
#include"CGameScene.h"
#include"CGameCamera.h"

void CGameScene::Init()
{
	g_camera.Init();
	m_ground.Init();
	m_player.Init();
	m_object.Init();
}

void CGameScene::Update()
{
	g_camera.BeforeUpdate();
	m_ground.Update();
	m_player.Update();
	m_object.Update();
	g_camera.Update();
}

void CGameScene::Render()
{
	m_player.Render();
	m_ground.Render();
	m_object.Render();
}

void CGameScene::Release()
{
	
}
