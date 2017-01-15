/**
 * @file Source\Title\GUI\TitleStart.h
 *
 * タイトルスタートクラスの定義.
 */
#pragma once

/**
 * タイトルスタートクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleStart : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleStart()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleStart()
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

	/** スタート画像. */
	Image StartImage_;
	/** スタート画像用トランスフォーム. */
	RectTransform StartRT_;

};