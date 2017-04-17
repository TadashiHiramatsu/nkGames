/**
* メニューシステムクラスの定義.
*/
#pragma once

#include"MenuBar.h"

#include"Inventory/InventoryWindow.h"
#include"Option\OptionWindow.h"

#include"../../Player/Player.h"

/**
* メニューシステムクラス.
*/
class MenuSystem : public IGameObject
{
private:

	/** ウィンドウの状態. */
	enum WindowStateE
	{
		WindowBegin = 0,			//!< 先頭.
		Inventory = WindowBegin,	//!< 所持品.
		Option,						//!< 設定.
		WindowEnd = Option,			//!< 終端.
	};

public:

	/**
	* コンストラクタ.
	*/
	MenuSystem()
	{
	}

	/**
	* デストラクタ.
	*/
	~MenuSystem()
	{
	}

	/** 
	* 初期化.
	*/
	void Start(Player* player);

	/** 
	* 更新.
	*/
	void Update()override;
	
	/**
	* 描画.
	*/
	void PostRender()override;

	/**
	* 有効フラグの取得.
	*/
	bool GetEffectiveness() const
	{
		return isEffectiveness_;
	}

private:

	/** 有効フラグ. */
	bool isEffectiveness_ = false;

	/** メニューバー. */
	MenuBar MenuBar_;

	Image SelectImage_;
	RectTransform SelectRT_;

	/** ウィンドウの数. */
	static const int WINDOW_NUM = 2;

	/** ウィンドウの状態. */
	int WindowState_ = WindowStateE::Inventory;

	/** ウィンドウ. */
	unique_ptr<IMenuWindow> IMenuWindow_[WINDOW_NUM];

};

extern MenuSystem* g_MenuSystem;