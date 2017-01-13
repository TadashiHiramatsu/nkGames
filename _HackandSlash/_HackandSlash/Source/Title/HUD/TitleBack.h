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
 * @date 2017/01/11
 */
class TitleBack : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	TitleBack();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~TitleBack();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * ポストエフェクト後の描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void PostRender()override;

	/**
	 * Imageクラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/12
	 *
	 * @return The image.
	 */
	Image& GetImage()
	{
		return BackImage_;
	}

private:

	/** 背景画像. */
	Image BackImage_;
	/** 背景画像用トランスフォーム. */
	RectTransform BackRT_;

};