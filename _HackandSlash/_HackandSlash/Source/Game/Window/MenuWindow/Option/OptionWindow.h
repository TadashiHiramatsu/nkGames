/**
* メニューウィンドウのオプションウィンドウクラスの定義.
*/
#pragma once

#include"../IMenuWindow.h"

/**
* メニューウィンドウのオプションウィンドウクラス.
*/
class OptionWindow : public IMenuWindow
{
private:

	/** 状態コード. */
	enum SelectStateE
	{
		SelectBegin = 0,	//!< 状態の先頭.
		Save = SelectBegin,	//!< セーブ.
		Title,				//!< タイトル.
		Exit,				//!< エグジット.
		SelectEnd = Exit,	//!< 状態の終端.
		SelectNum,			//!< 数.
	};

public:

	/**
	* コンストラクタ.
	*/
	OptionWindow()
	{
	}

	/**
	* デストラクタ.
	*/
	~OptionWindow()
	{
	}

	/**
	* 初期化.
	*/
	void Start(RectTransform* rt, float namepos)override;

	/**
	* 更新.
	*/
	void Update()override;

	/**
	* 描画.
	*/
	void Render()override;

	/**
	* ウィンドウを閉じるときの動作.
	*/
	void Close()override
	{
	}

private:

	/** 
	* 選択移動. 
	*/
	bool SelectUpDownMove();

	/**
	* 決定.
	*/
	void Decision();

private:

	/** 画像. */
	Image WindowImage_;
	/** 画像用トランスフォーム. */
	RectTransform WindowRT_;

	Image ControllerImage_;
	RectTransform ControllerRT_;

	/** 選択している状態. */
	int SelectState_ = SelectStateE::Save;

	/** セレクトフレーム画像. */
	Image SelectFrameImage_[SelectStateE::SelectNum];
	/** セレクトフレーム用トランスフォーム. */
	RectTransform SelectFrameRT_[SelectStateE::SelectNum];

	Text OptionName_[SelectStateE::SelectNum];
	RectTransform OptionNameRT_[SelectStateE::SelectNum];


	Image SelectImage_;
	RectTransform SelectRT_;

};