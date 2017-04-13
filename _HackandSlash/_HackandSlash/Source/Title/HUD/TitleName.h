/**
* タイトルシーンのゲームタイトル表示クラスの定義.
*/
#pragma once

/**
* タイトルシーンのゲームタイトル表示クラス.
*/
class TitleName : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	TitleName()
	{
	}

	/**
	* デストラクタ.
	*/
	~TitleName()
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
	* フェードフラグの取得.
	*/
	bool IsFade()
	{
		return isFade_;
	}

private:

	/** タイトルネーム画像. */
	Image TitleNameImage_;
	/** タイトルネーム用トランスフォーム. */
	RectTransform TitleNameRT_;

	/** フェードフラグ. */
	bool isFade_ = false;

	/** フェードの速度. */
	float FadeSpeed;


};