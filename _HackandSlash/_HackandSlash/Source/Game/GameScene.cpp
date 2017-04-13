/**
 * @file	Source\Game\GameScene.cpp
 *
 * ゲームシーンクラスの実装.
 */
#include"stdafx.h"
#include"GameScene.h"

#include"AnimationEvent\CollisionWorld.h"

#include"GameCamera.h"
#include"GameLight.h"

#include"Player\Player.h"

#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Map\Map.h"

#include"HUD\LifeGage.h"
#include"HUD\ExpGage.h"

#include"Item\ItemDataResource.h"
#include"Window\MenuWindow\MenuSystem.h"

#include"DropItem\DropItemManager.h"

#include"Enemy\Spawn\EnemySpawnManager.h"

#include"../Common/SceneEffect/Fade.h"

#include"Boss/Warlock/Boss_Warlock.h"


/** コリジョンワールドのグローバルポインタ. */
CollisionWorld* g_CollisionWorld = nullptr;

/** メインカメラのグローバルポインタ. */
GameCamera* g_MainCamera = nullptr;

/** メニューシステムのグローバルポインタ. */
MenuSystem* g_MenuSystem = nullptr;

/** ドロップアイテムマネージャのグローバルポインタ. */
DropItemManager* g_DropItemManager = nullptr;

/** ゲームライトクラスのグローバルポインタ. */
GameLight* g_GameLight = nullptr;

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void GameScene::Start()
{
	//グラフィックコンフィグの設定
	GraphicsConfig_.ShadowConfig_.isEnable_ = true;
	GraphicsConfig_.ShadowConfig_.isSoftShadowMap_ = true;
	GraphicsConfig_.ShadowConfig_.ShadowMapW_ = 2048;
	GraphicsConfig_.ShadowConfig_.ShadowMapH_ = 2048;
	GraphicsConfig_.ShadowConfig_.Far_ = 40.0f;
	GraphicsConfig_.ShadowConfig_.Near_ = 2.0f;

	GraphicsConfig_.BloomConfig_.isEnable_ = true;
	GraphicsConfig_.AntiAliasingConfig_.isEnable_ = true;

	//アイテムデータのロード
	ItemDataResource().Load();

	//コリジョンワールドの作成
	g_CollisionWorld = NewGO<CollisionWorld>();
	
	//メインカメラの作成
	g_MainCamera = NewGO<GameCamera>(1);

	//ゲームライトの初期化
	g_GameLight = new GameLight();
	g_GameLight->Start();

	//地面作成
	NewGO<Ground>();
	//マップ作成
	NewGO<Map>();
	//スカイボックス
	Skybox* skybox = NewGO<Skybox>();

	//プレイヤーの作成
	Player* player = NewGO<Player>();

	//ゲームカメラにプレイヤーを設定
	g_MainCamera->SetPlayer(player);
	
	//スカイボックスにプレイヤーのポインタを設定.
	skybox->SetPlayer(player);

	//エネミースポナークラスの初期化
	EnemySpawnManager* esm = NewGO<EnemySpawnManager>();
	esm->SetPlayer(player);

	//ライフゲージ
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);

	//経験値バー
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

	//UI
	g_MenuSystem = NewGO<MenuSystem>();
	g_MenuSystem->Start(player);

	//インベントリの初期化
	InventoryManager().Start();

	//ドロップアイテムマネージャの作成
	g_DropItemManager = NewGO<DropItemManager>(3);
	g_DropItemManager->SetPlayer(player);

	Boss_Warlock* boss = NewGO<Boss_Warlock>();
	boss->SetPlayer(player);

	SoundSource* BGM = NewGO<SoundSource>();
	BGM->InitStreaming("Game/BGM");
	BGM->Play(true);

	//フェードクラスの作成
	Fade* fade = NewGO<Fade>(5);
	fade->StartFadeIn();
	
}
