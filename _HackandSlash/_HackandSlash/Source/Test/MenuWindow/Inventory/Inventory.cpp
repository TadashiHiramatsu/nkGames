#include"stdafx.h"
#include"Inventory.h"

void Inventory::Start(RectTransform * rt, float namepos)
{
	SelectIconSize_ = 70;

	NameStart(rt, "Image/Inventory.png", namepos);

	ChoiceImage_.Load("Image/Test.png");
	ChoiceImage_.SetTransform(&ChoiceTransform_);

	ChoiceTransform_.Parent_ = rt;
	ChoiceTransform_.Width_ = 280;
	ChoiceTransform_.Height_ = 600;
	ChoiceTransform_.Position_.x = -280;
	ChoiceTransform_.Pivot_.y = 1;

	DetailImage_.Load("Image/Test.png");
	DetailImage_.SetTransform(&DetailTransform_);

	DetailTransform_.Parent_ = rt;
	DetailTransform_.Width_ = 540;
	DetailTransform_.Height_ = 600;
	DetailTransform_.Position_.x = 150;
	DetailTransform_.Pivot_.y = 1;

	//中間トランスフォームの位置調整.
	MiddleImage_.Load("Image/Middle.png");
	MiddleImage_.SetTransform(&MiddleTransform_[0]);

	MiddleTransform_[0].Width_ = 250;
	MiddleTransform_[0].Height_ = 250;
	MiddleTransform_[0].Parent_ = &ChoiceTransform_;
	MiddleTransform_[0].Position_.y = 120;

	MiddleTransform_[1].Parent_ = &ChoiceTransform_;
	MiddleTransform_[1].Position_.y = 120;
	MiddleTransform_[1].RotationZ(45);

	float fpos = 110;

	D3DXVECTOR3 pos[4] =
	{
		{  fpos,     0, 0 },
		{     0,  fpos, 0 },
		{ -fpos,     0, 0 },
		{     0, -fpos, 0 }
	};

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconBackImage_[i].Load("Image/IconBack.png");
		IconBackImage_[i].SetTransform(&IconBackTransform_[i]);

		//偶数が回転していない
		IconBackTransform_[i].Parent_ = &MiddleTransform_[i % 2];

		if (i % 2 == 1)
		{
			IconBackTransform_[i].RotationZ(-45);
		}

		IconBackTransform_[i].Width_ = 60;
		IconBackTransform_[i].Height_ = 60;
		IconBackTransform_[i].Position_ = pos[i / 2];

	}

	IconImage_[0].Load("Icon/hand.png");		//腕
	IconImage_[1].Load("Icon/torso.png");		//胴
	IconImage_[2].Load("Icon/head.png");		//頭
	IconImage_[3].Load("Icon/shield.png");		//盾
	IconImage_[4].Load("Icon/sword.png");		//剣
	IconImage_[5].Load("Icon/necklace.png");	//アクセ
	IconImage_[6].Load("Icon/necklace.png");	//アクセ
	IconImage_[7].Load("Icon/leg.png");			//脚

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconImage_[i].SetTransform(&IconTransform_[i]);

		IconTransform_[i].Parent_ = &IconBackTransform_[i];

		IconTransform_[i].Width_ = DefaultIconSize_;
		IconTransform_[i].Height_ = DefaultIconSize_;
	}

	SelectName_.Create(20, 20);
	SelectName_.SetTransform(&TextTransform_);
	TextTransform_.Parent_ = &DetailTransform_;
	TextTransform_.Anchor_ = RectTransform::AnchorPresetE::TopCenter;
	TextTransform_.Position_.y = 70;

}

void Inventory::Update()
{
	ChoiceTransform_.Update();
	DetailTransform_.Update();

	MiddleTransform_[0].Update();
	MiddleTransform_[1].Update();

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconBackTransform_[i].Update();
	}

	IconUpdate();

	TextTransform_.Update();

}

void Inventory::Render()
{
	ChoiceImage_.Render();
	DetailImage_.Render();
	
	MiddleImage_.Render();

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconBackImage_[i].Render();

		IconImage_[i].Render();
	}

	char* Name[MAX_EQUIPMENT] =
	{
		"アーム",
		"アーマー",
		"ヘルム",
		"シールド",
		"ソード",
		"アクセサリー",
		"アクセサリー",
		"グリーヴ",
	};

	SelectName_.Render(Name[SelectEquipment_]);
}

void Inventory::IconUpdate()
{

	float angle = XInput().GetLeftStickAngle();

	D3DXVECTOR2 LeftStick = XInput().GetLeftStick();

	if (D3DXVec2Length(&LeftStick) > 0.0f)
	{
		SelectEquipment_ = (int)angle / (360 / MAX_EQUIPMENT);
	}

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		if (SelectEquipment_ == i)
		{
			IconTransform_[i].Width_ = SelectIconSize_;
			IconTransform_[i].Height_ = SelectIconSize_;
		}
		else
		{
			IconTransform_[i].Width_ = DefaultIconSize_;
			IconTransform_[i].Height_ = DefaultIconSize_;
		}

		IconTransform_[i].Update();

	}
}
