/**
 * @file Source\Game\Sprite\DropItem.cpp
 *
 * ドロップアイテムクラスの実装.
 */
#include"stdafx.h"
#include"DropItem.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param [in,out] item   If non-null, the item.
 * @param [in,out] camera If non-null, the camera.
 * @param [in,out] pos    The position.
 */
void DropItem::Start(IItem* item, Camera* camera, D3DXVECTOR3 & pos)
{
	//アイテムデータをコピー
	Item_ = item;

	//アイコンの読み込み
	ItemSprite_.Load(Item_->GetIconFilePath());
	ItemSprite_.Start();

	//カメラを設定
	ItemSprite_.SetCamera(camera);
	Camera_ = camera;

	//トランスフォームを設定
	ItemSprite_.SetTransform(&Transform_);

	//ポジションを設定
	Transform_.Position_ = pos + D3DXVECTOR3(0, 0.1f, 0);

	Transform_.Scale_ = D3DXVECTOR3(0.1f, 0.1f, 1);

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::Update()
{
	//カメラの回転行列を取得
	D3DXMATRIX rot = Camera_->GetRotationMatrix();

	//トランスフォームの更新
	Transform_.BillboardUpdate(rot);
}

/**
 * ポストエフェクト後の描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
void DropItem::PostRender()
{
	//スプライトの表示
	ItemSprite_.Render();
}
