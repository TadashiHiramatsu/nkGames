#pragma once

#include"MenuBar.h"

#include"Inventory/Inventory.h"
#include"../../Player/Player.h"

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
	void Start(Player* player);

	//更新
	void Update()override;
	
	//描画
	void PostRender()override;

	bool GetEffectiveness()
	{
		return isEffectiveness_;
	}

private:

	/** 有効フラグ. */
	bool isEffectiveness_ = false;

	/** メニューバー. */
	MenuBar MenuBar_;

	/** ウィンドウ*/
	unique_ptr<IMenuWindow> IMenuWindow_;

};

extern MenuSystem* g_MenuSystem;