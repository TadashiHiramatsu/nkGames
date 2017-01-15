/**
 * @file Source\Title\TitleCamera.h
 *
 * タイトルカメラクラスの定義.
 */
#pragma once

/**
 * タイトルカメラクラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
class TitleCamera : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	TitleCamera()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 */
	~TitleCamera()
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
	 * カメラクラスの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/14
	 *
	 * @return Null if it fails, else the camera.
	 */
	Camera* GetCamera()
	{
		return &Camera_;
	}

private:

	/** カメラ. */
	Camera Camera_;

};