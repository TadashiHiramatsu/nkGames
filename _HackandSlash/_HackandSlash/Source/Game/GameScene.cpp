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
//#include"GUI\InventoryWindow.h"
#include"HUD\LifeGage.h"
#include"HUD\ExpGage.h"

#include"Item\ItemResource.h"

/** コリジョンワールド. */
CollisionWorld* g_CollisionWorld = nullptr;

/** メインカメラ. */
GameCamera* g_MainCamera = nullptr;

/** インベントリウィンドウ. */
//InventoryWindow* g_Inventory = nullptr;

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
	GraphicsConfig_.ShadowConfig_.Fur_ = 100.0f;

	//コリジョンワールドの作成
	g_CollisionWorld = NewGO<CollisionWorld>();
	//メインカメラの作成
	g_MainCamera = NewGO<GameCamera>(1);

	//アイテムデータのロード
	ItemResource().Load();

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

	//UI
	//g_Inventory = NewGO<InventoryWindow>();
	
	//ライフゲージ
	LifeGage* lifeGage = NewGO<LifeGage>();
	lifeGage->SetPlayer(player);
	//経験値バー
	ExpGage* expGage = NewGO<ExpGage>();
	expGage->SetPlayer(player);

}
