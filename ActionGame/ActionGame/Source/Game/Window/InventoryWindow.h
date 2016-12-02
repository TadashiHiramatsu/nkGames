#pragma once

#include"ItemSlot.h"

//GUIWindowクラス武器やアイテムを見たり設定したりできる
class InventoryWindow : public IGameObject
{
public:

	//コンストラクタ
	InventoryWindow();
	//デストラクタ
	~InventoryWindow();

public:

	//初期化
	void Start()override;
	//更新
	void Update()override;
	//描画
	void Render()override;

	bool SetItem(IItem* _item);

private:
	Image IWSkin;
	RectTransform rectTransform;

	int ISlotNum;
	shared_ptr<CTexture> IFrameTex;
	vector<ItemSlot*> ISlotVec;

	bool isRender;
};

extern InventoryWindow* g_Inventory;