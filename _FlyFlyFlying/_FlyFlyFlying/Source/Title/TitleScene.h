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
 * @date 2017/01/14
 */
class TitleScene : public IScene
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleScene()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleScene()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	void Start()override;

};