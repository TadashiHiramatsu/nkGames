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
	DropItem()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~DropItem()
	{
	}

	/**
	* 初期化.
	* オーバーライドしていない.
	* 自分で呼ぶ必要あり.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/16
	*
	* @param [in,out] item   If non-null, the item.
	* @param [in,out] pos    The position.
	*/
	void Start(IItem* item, D3DXVECTOR3& pos);

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
	void Render()override;

private:

	/** アイテムのスプライト. */
	Sprite ItemSprite_;
	/** アイテムデータ. */
	IItem* Item_;

};