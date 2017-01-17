/**
 * @file Source\Game\Monster\IMonster.cpp
 *
 * モンスターの基底クラスの実装.
 */
#include"stdafx.h"
#include"IMonster.h"

#include"..\GameCamera.h"

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IMonster::IMonster():
	Radius_(0.4f),
	Height_(0.3f),
	Hp_(10),
	Distance_(10),
	toPlayerMaxDis_(20),
	PlayerAttackDis_(0.3f),
	WaitingTime_(4),
	WaitingLT_(0),
	Destination_(D3DXVECTOR3(0, 0, 0))
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IMonster::~IMonster()
{
	Release();
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Start()
{
	//トランスフォームの設定
	ModelRender_.SetTransform(&Transform_);
	//ライトの設定
	ModelRender_.SetLight(&Light_);
	//カメラ
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//シャドウレシーバキャスタ
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Update()
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
void IMonster::Render()
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
void IMonster::Release()
{
	//キャラクターコントローラの剛体を削除
	CharacterController_.RemoveRigidBody();
}