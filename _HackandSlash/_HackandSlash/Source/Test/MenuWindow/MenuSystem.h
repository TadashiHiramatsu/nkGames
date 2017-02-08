#pragma once

#include"MenuBar.h"

#include"Inventory/Inventory.h"

class MenuSystem : public IGameObject
{
public:

	/** コンストラクタ. */
	MenuSystem()
	{
	}

	/** デストラクタ. */
	~MenuSystem()
	{
	}

	//初期化
	void Start()override;

	//更新
	void Update()override;
	
	//描画
	void PostRender()override;

private:

	/** 有効フラグ. */
	bool isEffectiveness_ = false;

	/** メニューバー. */
	MenuBar MenuBar_;

	/** ウィンドウ*/
	unique_ptr<IMenuWindow> IMenuWindow_;

};