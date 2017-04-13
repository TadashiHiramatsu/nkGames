/**
* タイトルシーンのセレクトの基底クラスの定義.
*/
#pragma once

/**
* タイトルシーンのセレクトの基底クラス.
* タイトルのセレクトはすべてこれを継承する.
*/
class ITitleSelect : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	ITitleSelect()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~ITitleSelect()
	{
	}

	/**
	* 初期化.
	*/
	virtual void Start()override;

	/**
	* 更新.
	*/
	virtual void Update()override;

	/**
	* ポストエフェクト後の描画.
	*/
	virtual void PostRender()override;

	/**
	* 選択された時.
	*/
	virtual bool OnTrigger() = 0;

	/**
	* レクトトランスフォームの取得.
	*/
	RectTransform& GetRectTransform()
	{
		return SelectRT_;
	}

protected:

	/** 画像. */
	Image SelectImage_;
	/** トランスフォーム. */
	RectTransform SelectRT_;

};