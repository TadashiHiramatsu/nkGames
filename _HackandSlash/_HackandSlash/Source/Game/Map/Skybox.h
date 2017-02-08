/**
 * @file Source\Game\Map\Skybox.h
 *
 * スカイボックスクラスの定義.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * スカイボックスクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Skybox : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Skybox()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Skybox()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

	/**
	 * プレイヤーのポインタを設定.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] p If non-null, the pla.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** モデルレンダー. */
	ModelRender ModelRender_;
	/** ライト. */
	Light Light_;

	/** プレイヤーのポインタ. */
	Player* Player_;

};