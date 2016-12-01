#include"stdafx.h"
#include"GameScene.h"

#include"Player\Player.h"
#include"AnimationEvent\CollisionWorld.h"
#include"GameCamera.h"
#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Monster\MonsterHabitat.h"

//#include"GUIWindow\InventoryWindow.h"
//#include"Item\DropItemManager.h"

CollisionWorld* g_CollisionWorld = nullptr;
GameCamera* g_MainCamera = nullptr;
Player* g_Player = nullptr;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
	m_GraphicsConfig.ShadowConfig.isEnable = true;
	m_GraphicsConfig.ShadowConfig.isSoftShadowMap = true;
	m_GraphicsConfig.ShadowConfig.ShadowMapW = 2048;
	m_GraphicsConfig.ShadowConfig.ShadowMapH = 2048;
	m_GraphicsConfig.ShadowConfig.Fur = 100.0f;

	g_CollisionWorld = NewGO<CollisionWorld>();
	g_MainCamera = NewGO<GameCamera>();

	g_Player = NewGO<Player>();
	g_MainCamera->SetPlayerPointer(g_Player);
	
	NewGO<Ground>();
	Skybox* skybox = NewGO<Skybox>();
	skybox->SetPlayerPointer(g_Player);

	NewGO<MonsterHabitat>();
}
