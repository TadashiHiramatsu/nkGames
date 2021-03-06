/**
 * @file Source\Game\Map\Skybox.cpp
 *
 * スカイボックスクラスの実装.
 */
#include"stdafx.h"
#include"Skybox.h"

#include"..\GameCamera.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Start()
{
	//モデルをロード
	ModelRender_.Load("Skybox.x", nullptr);
	//カメラの設定
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//トランスフォームの設定
	ModelRender_.SetTransform(&Transform_);
	//ライトの設定
	ModelRender_.SetLight(&Light_);

	ModelRender_.SetFogParam(ModelRender::FogFuncE::FogFuncHeight, 150.0f, 0.0f, Vector4(1, 1, 1, 1));

	//環境光を最大にしてライティングを消す
	Light_.SetAmbientLight(Vector3::One);

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Update()
{
	//親子関係に変更してもいいかも
	//ポジションをプレイヤーの位置に
	Transform_.Position_ = Player_->Transform_.Position_;
	Transform_.Position_.y = 0;

	//トランスフォームの更新
	Transform_.Update();

	//モデルの更新
	ModelRender_.Update();

}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Render()
{
	//モデルを表示
	ModelRender_.Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Release()
{
	//モデルの解放
	ModelRender_.Release();

}