#include"stdafx.h"
#include"EquipmentDetailRender.h"

void EquipmentDetailRender::Start(RectTransform * parent)
{
	BackImage_.Load("Image/Test.png");
	BackImage_.SetTransform(&BackTransform_);
	BackTransform_.Parent_ = parent;
	BackTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomRight;
	BackTransform_.Pivot_ = D3DXVECTOR2(1, 0);
	BackTransform_.Position_ = D3DXVECTOR3(-15, 20, 0);
	BackTransform_.Width_ = parent->Width_ / 2 - 20;
	BackTransform_.Height_ = 510;

	ItemNameText_.Create(15, 15);
	ItemNameText_.SetTransform(&ItemNameTransform_);
	ItemNameTransform_.Parent_ = &BackTransform_;
	ItemNameTransform_.Anchor_ = RectTransform::TopCenter;
	ItemNameTransform_.Position_.y = 10;
}

void EquipmentDetailRender::Update()
{
	BackTransform_.Update();

	ItemNameTransform_.Update();
}

void EquipmentDetailRender::Render(EquipmentItem* item)
{
	BackImage_.Render();

	if (item != nullptr)
	{
		ItemNameText_.Render(item->GetName());
	}
}
