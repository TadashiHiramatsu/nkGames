/**
 * @file	Source\Game\GameScene.cpp
 *
 * ゲームシーンクラスの実装.
 */
#include"stdafx.h"
#include"GameScene.h"

#include"Player\Player.h"
#include"AnimationEvent\CollisionWorld.h"
#include"GameCamera.h"
#include"Map\Ground.h"
#include"Map\Skybox.h"
#include"Monster\MonsterHabitat.h"
#include"HUD\LifeGage.h"
#include"HUD\ExpGage.h"

#include"Item\ItemDataResource.h"
#include"Window\MenuWindow\MenuSystem.h"

#include"DropItem\DropItemManager.h"

/** コリジョンワールド. */
CollisionWorld* g_CollisionWorld = nullptr;

/** メインカメラ. */
GameCamera* g_MainCamera = nullptr;

/** メニューシステム. */
MenuSystem* g_MenuSystem = nullptr;

/** ドロップアイテムマネージャ. */
DropItemManager* g_DropItemManager = nullptr;

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

	//コリジョンワールドの作成
	g_CollisionWorld = NewGO<CollisionWorld>();
	//メインカメラの作成
	g_MainCamera = NewGO<GameCamera>(1);

	//アイテムデータのロード
	ItemDataResource().Load();

	//プレイヤーの作成
	Player* player = NewGO<Player>();

	//ゲームカメラにプレイヤーを設定
	g_MainCamera->SetPlayer(player);
	
	//地面
	NewGO<Ground>();

	//スカイボックス
	Skybox* skybox = NewGO<Skybox>();
	skybox->SetPlayer(player);

	//モンスターの住処
	MonsterHabitat* mh = NewGO<MonsterHabitat>();
	mh->SetPlayer(player);

	//ライフゲージ
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);

	//経験値バー
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

	//UI
	g_MenuSystem = NewGO<MenuSystem>();
	g_MenuSystem->Start(player);

	InventoryManager().Start();

	g_DropItemManager = NewGO<DropItemManager>();
	g_DropItemManager->SetPlayer(player);

}
