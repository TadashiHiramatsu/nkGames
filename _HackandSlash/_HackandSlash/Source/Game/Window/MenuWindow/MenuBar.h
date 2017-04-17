/**
* メニューバークラスの定義.
*/
#pragma once

/**
* メニューバークラス.
*/
class MenuBar : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	MenuBar()
	{
	}

	/**
	* デストラクタ.
	*/
	~MenuBar()
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
	* 描画.
	*/
	void Render()override;

	/** 
	*トランスフォームの取得. 
	*/
	RectTransform* GetTransform()
	{
		return &BarTransform_;
	}

private:

	/** 本体の画像. */
	Image BarImage_;
	/** 本体のトランスフォーム. */
	RectTransform BarTransform_;

};