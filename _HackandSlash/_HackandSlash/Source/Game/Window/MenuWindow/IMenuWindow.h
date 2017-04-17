/**
* メニューウィンドウの基底クラスの定義.
*/
#pragma once

#include"../../Player/Player.h"

/**
* メニューウィンドウの基底クラス.
*/
class IMenuWindow
{
public:

	/**
	* コンストラクタ.
	*/
	IMenuWindow()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~IMenuWindow()
	{
	}

	/** 
	* 初期化
	*/
	virtual void Start(RectTransform* rt, float namepos) = 0;

	/**
	* 更新
	*/
	virtual void Update() = 0;

	/**
	* 描画
	*/
	virtual void Render() = 0;

	/**
	* 表示名の初期化.
	*/
	void NameStart(RectTransform* parent, const char* filepath, float pos,float width);

	/**
	* 表示名の更新
	*/
	void NameUpdate()
	{
		NameTransform_.Update();
	}

	/**
	* 表示名の描画
	*/
	void NameRender()
	{
		NameImage_.Render();
	}

	/**
	* 表示名のレクトトランスフォームを取得.
	*
	* @return	レクトトランスフォーム.
	*/
	const RectTransform& GetNameTransform() const
	{
		return NameTransform_;
	}

	RectTransform* GetNameTransformPointer()
	{
		return &NameTransform_;
	}

	/** 
	* ウィンドウを閉じるときの処理.
	*/
	virtual void Close() 
	{
	}

	/**
	* プレイヤーのポインタを設定.
	*/
	void SetPlayer(Player* player)
	{
		Player_ = player;
	}

protected:

	/** 名前画像. */
	Image NameImage_;
	/** 名前トランスフォーム. */
	RectTransform NameTransform_;

	/** プレイヤーのポインタ. */
	Player* Player_ = nullptr;

};
