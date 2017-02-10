#pragma once

#include"../../Item/EquipmentItem.h"

class EquipmentDetailRender
{
public:

	//初期化
	void Start(RectTransform* parent);

	//更新
	void Update();

	//描画
	void Render(EquipmentItem* item);

private:

	/** バック画像. */
	Image BackImage_;
	RectTransform BackTransform_;

	Text ItemNameText_;
	RectTransform ItemNameTransform_;

};