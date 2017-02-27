/**
 * @file Source\Game\Sprite\DropItem.cpp
 *
 * ドロップアイテムクラスの実装.
 */
#include"stdafx.h"
#include"DropItem.h"

#include"../GameCamera.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param [in,out] item   If non-null, the item.
 * @param [in,out] pos    The position.
 * @param [in,out] player プレイヤーのポインタ.
 */
void DropItem::Start(EquipmentItem* item, D3DXVECTOR3 & pos, Player* player)
{
	//アイテムデータをコピー
	Item_ = item;

	//アイコンの読み込み
	ItemSprite_.Load(Item_->GetIconFilePath());
	ItemSprite_.Start();

	//カメラを設定
	ItemSprite_.SetCamera(g_MainCamera->GetCamera());

	//トランスフォームを設定
	ItemSprite_.SetTransform(&Transform_);

	//ポジションを設定
	Transform_.Position_ = pos + D3DXVECTOR3(0, 0.3f, 0);

	//大きさを調整
	Transform_.Scale_ = D3DXVECTOR3(0.2f, 0.2f, 1.0f);

	//プレイヤーの位置ベクトルのポインタを設定
	PlayerPos_ = &player->Transform_.Position_;

	//カメラの回転行列を取得
	D3DXMATRIX rot = g_MainCamera->GetCamera()->GetRotationMatrix();
	//トランスフォームの更新
	Transform_.BillboardUpdate(rot);
}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::Update()
{
	//プレイヤーへのベクトルを求める
	D3DXVECTOR3 toPlayer = *PlayerPos_ - Transform_.Position_;

	//距離を代入
	toPlayerLength_ = D3DXVec3Length(&toPlayer);

	//カメラの回転行列を取得
	D3DXMATRIX rot = g_MainCamera->GetCamera()->GetRotationMatrix();

	//トランスフォームの更新
	Transform_.BillboardUpdate(rot);
}

/**
 * ポストエフェクト後の描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::Render()
{
	//スプライトの表示
	ItemSprite_.Render();
}
