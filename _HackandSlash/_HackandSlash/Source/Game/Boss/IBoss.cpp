/**
* ボスの基底クラスの実装.
*/
#include"stdafx.h"
#include"IBoss.h"

#include"../GameCamera.h"
#include"../GameLight.h"

/**
* 初期化.
*/
void IBoss::Start()
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
*/
void IBoss::Update()
{
	//トランスフォームの更新
	Transform_.Update();

	//モデルの更新
	ModelRender_.Update();
}

/**
* 描画.
*/
void IBoss::Render()
{
	//モデルの表示
	ModelRender_.Render();
}

/**
* 解放.
*/
void IBoss::Release()
{
}
