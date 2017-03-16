#include"stdafx.h"
#include"EquipmentDetailRender.h"

void EquipmentDetailRender::Start(RectTransform * parent)
{

	{//フレームの初期化
		FrameImage_.Load("Image/Test.png");
		FrameImage_.SetTransform(&FrameTransform_);
		FrameTransform_.Parent_ = parent;
		FrameTransform_.Anchor_ = AnchorPresetE::BottomRight;
		FrameTransform_.Pivot_ = Vector2(1, 0);
		FrameTransform_.Position_ = Vector3(-15, 20, 0);
		FrameTransform_.Width_ = parent->Width_ / 2 - 20;
		FrameTransform_.Height_ = 500;
	}

	{//バックの初期化
		BackImage_.Load("Image/Test.png");
		BackImage_.SetTransform(&BackTransform_);
		BackTransform_.Parent_ = &FrameTransform_;
		BackTransform_.Position_ = Vector3(0, -5, 0);
		BackTransform_.Anchor_ = AnchorPresetE::TopCenter;
		BackTransform_.Pivot_.y = 1;
		BackTransform_.Width_ = parent->Width_ / 2 - 30;
		BackTransform_.Height_ = 122;
	}

	{
		IconBackImage_.Load("Image/Test.png");
		IconBackImage_.SetTransform(&IconBackTransform_);
		IconBackTransform_.Parent_ = &BackTransform_;
		IconBackTransform_.Anchor_ = AnchorPresetE::MiddleLeft;
		IconBackTransform_.Pivot_.x = 0;
		IconBackTransform_.Width_ = 60;
		IconBackTransform_.Height_ = 115;
		IconBackTransform_.Position_.x = 5;
	}
	{
		IconImage_.Load();
		IconImage_.SetTransform(&IconTransform_);
		IconTransform_.Parent_ = &IconBackTransform_;
		IconTransform_.Width_ = 50;
		IconTransform_.Height_ = 50;
	}

	{//アイテム名の表示
		ItemNameText_.Create(10, 10);
		ItemNameText_.SetTransform(&ItemNameTransform_);
		ItemNameText_.SetFormat(Text::FormatE::Left);
		ItemNameTransform_.Parent_ = &IconBackTransform_;
		ItemNameTransform_.Anchor_ = AnchorPresetE::TopRight;
		ItemNameTransform_.Position_.x = 5;
	}

	{//パラメータ表示用テキスト
		ParameterText_.Create(25, 25);
		ParameterText_.SetTransform(&ParameterTransform_);
		//ParameterText_.SetColor(D3DXVECTOR4(255, 255, 255, 255));
		ParameterText_.SetFormat(Text::FormatE::Left);
		ParameterTransform_.Parent_ = &BackTransform_;
		ParameterTransform_.Anchor_ = AnchorPresetE::BottomLeft;
		ParameterTransform_.Position_ = Vector3(70, -30, 0);
	}
	{
		ParamNameText_.Create(10, 10);
		ParamNameText_.SetTransform(&ParamNameTransform_);
		ParamNameText_.SetFormat(Text::FormatE::Left);
		ParamNameTransform_.Parent_ = &BackTransform_;
		ParamNameTransform_.Anchor_ = AnchorPresetE::BottomRight;
		ParamNameTransform_.Position_ = Vector3(-70, -15, 0);
	}
}

void EquipmentDetailRender::Update()
{
	FrameTransform_.Update();

	BackTransform_.Update();

	IconBackTransform_.Update();
	IconTransform_.Update();
	ItemNameTransform_.Update();

	ParameterTransform_.Update();
	ParamNameTransform_.Update();
}

void EquipmentDetailRender::Render(EquipmentItem* item)
{
	FrameImage_.Render();

	BackImage_.Render();
	IconBackImage_.Render();

	if (item != nullptr)
	{
		IconImage_.Load(item->GetIconFilePath());
		IconImage_.Render();
		ItemNameText_.Render(item->GetName());

		int par = item->GetParameter();

		if (par >= 0)
		{
			char text[10];
			sprintf_s(text, "%d", par);
			char Name[10] = "";
			switch (item->GetItemType())
			{
			case Weapon:
				strcat(Name, "攻撃力");
				break;
			case Shield:
			case Helm:
			case Armor:
			case Arm:
			case Greaves:
				strcat(Name, "防御力");
				break;
			default:
				break;
			}
			ParameterText_.Render(text);
			ParamNameText_.Render(Name);
		}
	}
}
