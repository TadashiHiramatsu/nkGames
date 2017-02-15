#pragma once

#include"../../../Item/EquipmentItem.h"

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

	/** フレーム画像. */
	Image FrameImage_;
	RectTransform FrameTransform_;

	/** バック画像. */
	Image BackImage_;
	RectTransform BackTransform_;

	Image IconBackImage_;
	RectTransform IconBackTransform_;

	Image IconImage_;
	RectTransform IconTransform_;


	Text ItemNameText_;
	RectTransform ItemNameTransform_;

	Text ParameterText_;
	RectTransform ParameterTransform_;

	Text ParamNameText_;
	RectTransform ParamNameTransform_;

};