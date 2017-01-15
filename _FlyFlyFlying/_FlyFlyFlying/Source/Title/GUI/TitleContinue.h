/**
 * @file Source\Title\GUI\TitleContinue.h
 *
 * タイトルコンティニュークラスの定義.
 */
#pragma once

/**
 * タイトルコンティニュークラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
class TitleContinue : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	TitleContinue()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	~TitleContinue()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void Update()override;

	/**
	 * ポストエフェクト後の描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/15
	 */
	void PostRender()override;

private:

	/** コンティニュー画像. */
	Image ContinueImage_;
	/** コンティニュー画像用トランスフォーム. */
	RectTransform ContinueRT_;

};