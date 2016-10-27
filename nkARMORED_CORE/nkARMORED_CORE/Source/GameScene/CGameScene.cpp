#include"stdafx.h"
#include"CGameScene.h"
#include"CGameCamera.h"

void CGameScene::Init()
{
	m_GraphicsConfig.ShadowConfig.isEnable = true;
	m_GraphicsConfig.ShadowConfig.isSoftShadowMap = true;
	m_GraphicsConfig.ShadowConfig.ShadowMapW = 2048;
	m_GraphicsConfig.ShadowConfig.ShadowMapH = 2048;
	m_GraphicsConfig.ShadowConfig.Fur = 100.0f;

	g_Physics.Init();

	m_player.Init();
	g_camera.Init();
	m_ground.Init();

	//’n–Ê‚ÌMesh‚ð“n‚·
	m_player.SetMesh(m_ground.GetMesh());
	m_player.SetMatrixInv(m_ground.GetWorldInv());

	m_skybox.Init();
}

void CGameScene::Update()
{
	g_Physics.Update();

	g_camera.BeforeUpdate();

	m_ground.Update();
	m_player.Update();

	m_skybox.SetPosition(m_player.GetTrans()->GetPosition());
	m_skybox.Update();
	
	g_camera.Update();
}

void CGameScene::Render()
{
	m_player.Render();
	m_ground.Render();
	m_skybox.Render();
}

void CGameScene::Release()
{
	
}
