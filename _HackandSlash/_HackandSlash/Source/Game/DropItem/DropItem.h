/**
 * @file Source\Game\Sprite\DropItem.h
 *
 * ドロップアイテムクラスの定義.
 */
#pragma once

#include"../Item/EquipmentItem.h"
#include"../Player/Player.h"

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
	* @param [in] player     プレイヤーのポインタ
	*/
	void Start(EquipmentItem* item,const Vector3& pos, Player* player);

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

	/**
	* リストでソートするための関数.
	*/
	static bool Comp(DropItem* d1, DropItem* d2)
	{
		if (d1->toPlayerLength_ < d2->toPlayerLength_)
		{
			return true;
		}
		else
		{
			return (d1->toPlayerLength_ < d1->toPlayerLength_);
		}

		// NOTREACHED
		return false;
	}
	
	/** プレイヤーとの距離を取得. */
	float GettoPlayerLength()
	{
		return toPlayerLength_;
	}

	/** アイテムを取得. */
	EquipmentItem* GetEquipmentItem()
	{
		return Item_;
	}

private:

	/** アイテムのスプライト. */
	Sprite ItemSprite_;
	/** アイテムデータ. */
	EquipmentItem* Item_;

	/** プレイヤーの位置ベクトルのポインタ. */
	Vector3* PlayerPos_;

	/** プレイヤーとの距離. */
	float toPlayerLength_ = 0;

};