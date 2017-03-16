/**
 * @file	Source\Game\GUI\LifeGage.h
 *
 * プレイヤーのライフを描画するクラスの定義.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * ライフゲージクラス.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
class LifeGage : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	LifeGage()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	~LifeGage()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void Update()override;

	/**
	 * ポストエフェクトの後に呼ばれる描画.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 */
	void PostRender()override;

	/**
	 * プレイヤーのポインタを設定.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/30
	 *
	 * @param [in]	p	If non-null, the p.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** フレーム用. */
	RectTransform LifeFrameTransform_;
	/** フレームのImage. */
	Image LifeFrameImage_;
	/** 本体用. */
	RectTransform LifeTransform_;
	/** LifeのImage. */
	Image LifeImage_;

	/** ライフの数値を表示するフォント. */
	Text Life_;
	RectTransform TextTransform_;

	/** プレイヤーのポインタ. */
	Player* Player_;
	/** 現在の体力の最大値. */
	int* MaxLife_;
	/** 現在の体力の値. */
	int* NowLife_;

	D3DXVECTOR2 value;

};