#include"stdafx.h"
#include"GameScene.h"
#include"AnimationEvent\CollisionWorld.h"
#include"GameCamera.h"

#include"GUIWindow\InventoryWindow.h"

#include"Item\DropItemManager.h"

CollisionWorld* g_CollisionWorld = NULL;

Player* g_Player = nullptr;

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
	g_Player = &Player;

	TestMH.Init();

	Ground.Init();
	Skybox.Init();
	MainCamera.Init();

	Inventory().Init();

	MouseX.Create(50, 50, TestFont::FontWeights::NORMAL);
	MouseY.Create(50, 50, TestFont::FontWeights::NORMAL);

	DIManager().Init();
}

void GameScene::Update()
{
	g_CollisionWorld->Update();
	Player.Update();

	TestMH.Update();

	Ground.Update();
	Skybox.SetPosition(Player.GetPos());
	Skybox.Update();
	MainCamera.Update();

	Inventory().Update();

	DIManager().Update();
}

void GameScene::Render()
{
	g_CollisionWorld->Render();

	TestMH.Render();

	Ground.Render();
	Skybox.Render();
	Player.Render();

	Inventory().Render();

	DIManager().Render();

	MouseX.Render("X", Input.GetMousePosX(), D3DXVECTOR2(0, 100));
	MouseY.Render("Y", Input.GetMousePosY(), D3DXVECTOR2(0, 150));
}

void GameScene::Release()
{
	Player.Release();
	Ground.Release();
	Skybox.Release();
	MainCamera.Release();
}
