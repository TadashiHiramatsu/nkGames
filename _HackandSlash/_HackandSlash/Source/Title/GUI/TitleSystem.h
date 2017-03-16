/**
 * @file Source\Title\GUI\TitleSystem.h
 *
 * タイトルシステムクラスの定義.
 */
#pragma once

#include"../HUD/TitleBack.h"
#include"../../Common/SceneEffect/Fade.h"

/**
 * タイトルシステムクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
class TitleSystem : public IGameObject
{
public:

	/** タイトルの状態. */
	enum class TitleStateE
	{
		StartUp,	//!< 起動
		Run,		//!< 稼働
		BlackOut,	//!< ブラックアウト
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	TitleSystem()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	~TitleSystem()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 */
	void Start()override;

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

	/** タイトルネーム画像. */
	Image TitleNameImage_;
	/** タイトルネーム用トランスフォーム. */
	RectTransform TitleNameRT_;

	/** ニューゲーム画像. */
	Image NewGameImage_;
	/** ニューゲーム用トランスフォーム. */
	RectTransform NewGameRT_;

	/** コンティニュー画像. */
	Image ContinueImage_;
	/** コンティニュー用トランスフォーム. */
	RectTransform ContinueRT_;

	/** ステート. */
	TitleStateE State_ = TitleStateE::StartUp;

	/** フェードクラスのポインタ*/
	Fade* Fade_ = nullptr;

	/** タイトルBGM. */
	SoundSource* TitleBGM_ = nullptr;

};