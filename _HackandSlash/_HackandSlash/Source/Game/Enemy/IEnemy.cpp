/**
 * @file Source\Game\Monster\IEnemy.cpp
 *
 * 敵の基底クラスの実装.
 */
#include"stdafx.h"
#include"IEnemy.h"

#include"..\GameCamera.h"
#include"../GameLight.h"

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IEnemy::IEnemy():
	Radius_(0.3f),
	Height_(0.5f),
	Hp_(50),
	Distance_(10),
	toPlayerMaxDis_(20),
	PlayerAttackDis_(0.3f),
	WaitingTime_(4),
	WaitingLT_(0)
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IEnemy::~IEnemy()
{
	Release();
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Start()
{
	//トランスフォームの設定
	ModelRender_.SetTransform(&Transform_);
	//ライトの設定
	ModelRender_.SetLight(g_GameLight->GetLight());
	//カメラ
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//シャドウレシーバキャスタ
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Update()
{
	//トランスフォームの更新
	Transform_.Update();

	//モデルの更新
	ModelRender_.Update();

}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Render()
{
	//モデルの表示
	ModelRender_.Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Release()
{
	
}
