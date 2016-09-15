#include"stdafx.h"
#include"CGameScene.h"
#include"CGameCamera.h"

void CGameScene::Init()
{
	g_camera.Init();
	m_ground.Init();
	m_player.Init();
	//’n–Ê‚ÌMesh‚ð“n‚·
	m_player.SetMesh(m_ground.GetMesh());
	m_player.SetMatrixInv(m_ground.GetWorldInv());
	m_skybox.Init();
	m_building.Init();
}

void CGameScene::Update()
{
	g_camera.BeforeUpdate();

	m_ground.Update();
	m_player.Update();

	m_skybox.SetPosition(m_player.GetTrans()->GetPosition());
	m_skybox.Update();
	
	m_building.Update();

	g_camera.Update();
}

void CGameScene::Render()
{
	m_player.Render();
	m_ground.Render();
	m_skybox.Render();
	m_building.Render();

}

void CGameScene::Release()
{
	
}
