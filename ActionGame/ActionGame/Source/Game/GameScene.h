/**
 * @file Source\Game\GameScene.h
 *
 * ゲームシーンクラスの定義.
 */
#pragma once

/**
 * ゲームシーンクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class GameScene : public IScene
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	GameScene();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~GameScene();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

};