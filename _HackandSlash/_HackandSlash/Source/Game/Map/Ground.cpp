/**
 * @file Source\Game\Map\Ground.cpp
 *
 * グラウンドクラスの実装.
 */
#include"stdafx.h"
#include"Ground.h"

#include"..\GameCamera.h"
#include"../GameLight.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Start()
{
	//モデルのロード
	ModelRender_.Load("Ground.X",nullptr);
	//トランスフォームの設定
	ModelRender_.SetTransform(&Transform_);
	//ライトの設定
	ModelRender_.SetLight(g_GameLight->GetLight());
	//カメラの設定
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//シャドウキャスターの設定true.
	ModelRender_.SetShadowCasterFlag(true);
	//シャドウレシーバーの設定true.
	ModelRender_.SetShadowReceiverFlag(true);

	//法線マップの設定
	Normal_.Load("ground4_Normal.tga");
	ModelRender_.SetNormalMap(&Normal_);

	//スペキュラマップの設定
	Specular_.Load("ground4_Specular.tga");
	ModelRender_.SetSpecMap(&Specular_);

	ModelRender_.SetFogParam(ModelRender::FogFuncE::FogFuncDist, 350.0f, 600.0f, D3DXVECTOR4(1, 1, 1, 1));

	//更新
	Update();

	//ワールド行列の取得
	WorldMatrix_ = ModelRender_.FindBoneWorldMatrix("Plane002");

	//メッシュコライダーの作成
	MeshCollider_.Create(&ModelRender_, WorldMatrix_);
	
	//剛体の作成
	RigidBodyInfoS rbInfo;
	rbInfo.Collider_ = &MeshCollider_;
	rbInfo.Mass_ = 0.0f;
	RigidBody_.Create(rbInfo);

	//グラウンドタグを設定
	RigidBody_.GetBody()->setUserIndex(ECollisionAttr::CollisionAttr_Ground);

	//物理ワールドに追加
	Physics().AddRigidBody(&RigidBody_);

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Update()
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
 * @date 2017/01/10
 */
void Ground::Render()
{
	//モデルの描画
	ModelRender_.Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Release()
{
	//モデルの解放
	ModelRender_.Release();

}