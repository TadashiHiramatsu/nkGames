/**
* フェードクラスの定義.
*/
#pragma once

/**
* フェードクラス.
*/
class Fade : public IGameObject
{
public:

	/** フェードの状態. */
	enum FadeStateE
	{
		FadeIn,			//!< フェードイン.
		FadeOut,		//!< フェードアウト.
		FadeCompletion,	//!< フェード完了.
	};

public:

	/**
	* コンストラクタ.
	*/
	Fade()
	{
		SetActive(false);
	}

	/**
	* デストラクタ.
	*/
	~Fade()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;

	/**
	* 更新.
	*/
	void Update()override;

	/**
	* ポストエフェクト後の描画.
	*/
	void PostRender()override;

	/**
	* フェードアウト開始.
	*/
	void StartFadeOut()
	{
		State_ = FadeOut;
		FadeNowAlpha_ = 0;
		SetActive(true);
	}

	/**
	* フェードイン開始.
	*/
	void StartFadeIn()
	{
		State_ = FadeIn;
		FadeNowAlpha_ = 1;
		SetActive(true);
	}
	
	/**
	* 現在の状態を取得.
	*/
	FadeStateE GetState()
	{
		return State_;
	}

	/**
	* フェードの速さを設定.
	*/
	void SetFadeSpeed(float speed)
	{
		FadeSpeed_ = speed;
	}

private:

	/** フェードの画像描画. */
	Image FadeImage_;
	/** フェードのトランスフォーム. */
	RectTransform FadeTransform_;

	/** 現在のアルファ値. */
	float FadeNowAlpha_ = 0;

	/** フェードの状態. */
	FadeStateE State_ = FadeStateE::FadeCompletion;

	/** フェードの速さ(秒). */
	float FadeSpeed_ = 1;

};