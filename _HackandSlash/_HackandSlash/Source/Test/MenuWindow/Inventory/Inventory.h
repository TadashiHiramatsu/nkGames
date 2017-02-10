#pragma once

#include"../IMenuWindow.h"
#include"ItemDetailRender.h"

#include"../../Item/InventoryManager.h"

#include"../../Player/PlayerEquipment.h"
#include"../Inventory/EquipmentDetailRender.h"

class Inventory : public IMenuWindow
{
public:

	enum StateE
	{
		Select,	//選択
		Detail, //詳細
	};

public:

	void Start(RectTransform* rt, float namepos)override;
	void Update()override;
	void Render()override;

	//ウィンドウを閉じるときの動作
	void Close()override
	{
		ChangeState(StateE::Select);
	}

private:

	//ステートを変化
	void ChangeState(StateE state)
	{
		State_ = state;
	}

	void ChangeItem();

private:

	/** 最高装備数. */
	const static int MAX_EQUIPMENT = 8;

	//選択
	Image ChoiceImage_;
	RectTransform ChoiceTransform_;

	//位置調整のためのトランスフォーム
	Image MiddleImage_;
	RectTransform MiddleTransform_[2];

	//アイコンバック画像
	Image IconBackImage_[MAX_EQUIPMENT];
	RectTransform IconBackTransform_[MAX_EQUIPMENT];

	//アイコン画像
	Image IconImage_[MAX_EQUIPMENT];
	RectTransform IconTransform_[MAX_EQUIPMENT];

	/** 先頭引数. */
	int LeadIdx[MAX_EQUIPMENT];

	ItemTypeE SelectEquipmentCode[MAX_EQUIPMENT] = 
	{
		ItemTypeE::Arm,
		ItemTypeE::Armor,
		ItemTypeE::Helm,
		ItemTypeE::Shield,
		ItemTypeE::Sword,
		ItemTypeE::Accessory,
		ItemTypeE::Accessory,
		ItemTypeE::Greaves,
	};

	/** 選択中の装備. */
	int SelectEquipment_ = 0;

	/** 初期状態の大きさ. */
	float DefaultIconSize_ = 40;

	/**:選択時のアイコンの大きさ. */
	float SelectIconSize_ = 70;

	Text SelectName_;
	RectTransform SelectNameTransform_;

	//詳細
	Image DetailImage_;
	RectTransform DetailTransform_;

	const static int MAX_DISPLAY = 4;

	int BefSelect_[MAX_EQUIPMENT];
	int NowSelect_[MAX_EQUIPMENT];

	Image DetailSelectImage_;
	RectTransform DetailSelectTransform_;

	/** アイテム表示の枠. */
	ItemDetailRender ItemDetailRender_[MAX_DISPLAY];

	StateE State_;

	/** 装備アイテム描画. */
	EquipmentDetailRender EquipmentDetailRender_;
	
	PlayerEquipment PlayerEquipment_;

};