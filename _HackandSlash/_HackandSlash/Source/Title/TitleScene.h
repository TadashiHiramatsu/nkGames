/**
 * @file Source\Title\TitleScene.h
 *
 * タイトルシーンクラスの定義.
 */
#pragma once

/**
 * タイトルシーンクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class TitleScene : public IScene
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	TitleScene()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~TitleScene()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

};