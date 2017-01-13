/**
 * @file Source\Game\Sprite\DropItem.h
 *
 * ドロップアイテムクラスの定義.
 */
#pragma once

#include"../Item/IItem.h"

/**
 * ドロップアイテムクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class DropItem : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	DropItem();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~DropItem();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Start(IItem* item, Camera* camera, D3DXVECTOR3& pos);

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Update()override;

	/**
	 * ポストエフェクト後の描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void PostRender()override;

private:

	/** アイテムのスプライト. */
	Sprite ItemSprite_;
	/** アイテムデータ. */
	IItem* Item_;

};