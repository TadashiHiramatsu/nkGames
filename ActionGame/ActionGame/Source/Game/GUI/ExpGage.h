/**
 * @file	Source\Game\GUI\ExpGage.h
 *
 * 経験値ゲージクラスの定義.
 */
#pragma once

#include"..\Player\Player.h"

/**
 * 経験値ゲージクラス.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class ExpGage : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	ExpGage();

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~ExpGage();

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * ポストエフェクトの後に呼ばれる描画.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void PostRender()override;

	/**
	 * プレイヤーのポインタを設定.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	p	If non-null, the p.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** フレーム用. */
	RectTransform ExpFrameTransform_;
	/** フレームのImage. */
	Image ExpFrameImage_;
	/** 本体用. */
	RectTransform ExpTransform_;
	/** 本体のImage. */
	Image ExpImage_;

	/** プレイヤーのポインタ. */
	Player* Player_;
	/** 現在の必要経験値. */
	int* NextExp_;
	/** 現在の取得経験値. */
	int* NowExp_;

	/** 現在のレベルを表示する. */
	TestFont Level_;

};