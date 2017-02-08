#pragma once

#include"../IMenuWindow.h"

class Inventory : public IMenuWindow
{
public:

	void Start(RectTransform* rt, float namepos)override;
	void Update()override;
	void Render()override;

private:

	/**
	* アイコンの更新.
	*/
	void IconUpdate();

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
	
	/** 選択中の装備. */
	int SelectEquipment_ = 0;

	/** 初期状態の大きさ. */
	float DefaultIconSize_ = 40;

	/**:選択時のアイコンの大きさ. */
	float SelectIconSize_ = 60;

	Text SelectName_;
	RectTransform TextTransform_;

	//詳細
	Image DetailImage_;
	RectTransform DetailTransform_;

};