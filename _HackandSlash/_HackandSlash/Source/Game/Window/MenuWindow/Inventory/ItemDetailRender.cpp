#include"stdafx.h"
#include"ItemDetailRender.h"

void ItemDetailRender::Start(RectTransform* parent,const Vector3& pos)
{

	BackImage_.Load("Image/Test.png");
	BackImage_.SetTransform(&BackTransform_);
	BackTransform_.Parent_ = parent;
	BackTransform_.Position_ = pos;
	BackTransform_.Position_.x = 15;
	BackTransform_.Anchor_ = AnchorPresetE::TopLeft;
	BackTransform_.Pivot_ = Vector2(0, 1);
	BackTransform_.Width_ = parent->Width_ / 2 - 20;
	BackTransform_.Height_ = 122;

	IconBackImage_.Load("Image/Test.png");
	IconBackImage_.SetTransform(&IconBackTransform_);
	IconBackTransform_.Parent_ = &BackTransform_;
	IconBackTransform_.Anchor_ = AnchorPresetE::MiddleLeft;
	IconBackTransform_.Pivot_.x = 0;
	IconBackTransform_.Width_ = 60;
	IconBackTransform_.Height_ = 115;
	IconBackTransform_.Position_.x = 5;

	NameText_.Create(10, 10);
	NameText_.SetTransform(&NameTransform_);
	NameText_.SetFormat(Text::FormatE::Left);
	NameTransform_.Parent_ = &IconBackTransform_;
	NameTransform_.Anchor_ = AnchorPresetE::TopRight;
	NameTransform_.Position_.x = 5;

	IconImage_.Load();
	IconImage_.SetTransform(&IconTransform_);
	IconTransform_.Parent_ = &IconBackTransform_;
	IconTransform_.Width_ = 50;
	IconTransform_.Height_ = 50;

	{//パラメータ表示用テキスト
		ParameterText_.Create(25, 25);
		ParameterText_.SetTransform(&ParameterTransform_);
		//ParameterText_.SetColor(D3DXVECTOR4(255, 255, 255, 255));
		ParameterText_.SetFormat(Text::FormatE::Left);
		ParameterTransform_.Parent_ = &BackTransform_;
		ParameterTransform_.Anchor_ = AnchorPresetE::BottomLeft;
		ParameterTransform_.Position_ = Vector3(70,-30,0);
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

void ItemDetailRender::Update()
{
	BackTransform_.Update();
	IconBackTransform_.Update();
	IconTransform_.Update();
	NameTransform_.Update();
	ParameterTransform_.Update();
	ParamNameTransform_.Update();
}

void ItemDetailRender::Render(EquipmentItem * item)
{
	BackImage_.Render();
	IconBackImage_.Render();

	if (item != nullptr)
	{
		IconImage_.Load(item->GetIconFilePath().c_str());
		IconImage_.Render();
		NameText_.Render(item->GetName().c_str());

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
