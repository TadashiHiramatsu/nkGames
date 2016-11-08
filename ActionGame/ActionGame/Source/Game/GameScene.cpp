#include"stdafx.h"
#include"GameScene.h"
#include"AnimationEvent\CollisionWorld.h"
#include"GameCamera.h"

CollisionWorld* g_CollisionWorld = NULL;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_GraphicsConfig.ShadowConfig.isEnable = true;
	m_GraphicsConfig.ShadowConfig.isSoftShadowMap = true;
	m_GraphicsConfig.ShadowConfig.ShadowMapW = 2048;
	m_GraphicsConfig.ShadowConfig.ShadowMapH = 2048;
	m_GraphicsConfig.ShadowConfig.Fur = 100.0f;

	g_CollisionWorld = new CollisionWorld;
	g_CollisionWorld->Init();

	Player.Init();
	Monster.Init();
	Ground.Init();
	Skybox.Init();
	MainCamera.Init();
}

void GameScene::Update()
{
	g_CollisionWorld->Update();
	Player.Update();
	Monster.Update();
	Ground.Update();
	Skybox.SetPosition(Player.GetPos());
	Skybox.Update();
	MainCamera.Update();
}

void GameScene::Render()
{
	g_CollisionWorld->Render();
	Monster.Render();
	Ground.Render();
	Skybox.Render();
	Player.Render();
}

void GameScene::Release()
{
	Player.Release();
	Monster.Release();
	Ground.Release();
	Skybox.Release();
	MainCamera.Release();
}
