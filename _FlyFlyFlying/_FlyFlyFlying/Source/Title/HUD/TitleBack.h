/**
 * @file Source\Title\HUD\TitleBack.h
 *
 * タイトルバッククラスの定義.
 */
#pragma once

/**
 * タイトルバッククラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleBack : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleBack()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleBack()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Update()override;

	/**
	 * ポストエフェクト後の描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void PostRender()override;

private:

	/** 背景画像. */
	Image BackImage_;
	/** 背景画像用トランスフォーム. */
	RectTransform BackRT_;

};