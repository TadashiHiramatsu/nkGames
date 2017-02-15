#include"stdafx.h"
#include"ItemDetailRender.h"

void ItemDetailRender::Start(RectTransform* parent, D3DXVECTOR3& pos)
{

	BackImage_.Load("Image/Test.png");
	BackImage_.SetTransform(&BackTransform_);
	BackTransform_.Parent_ = parent;
	BackTransform_.Position_ = pos;
	BackTransform_.Position_.x = 15;
	BackTransform_.Anchor_ = RectTransform::AnchorPresetE::TopLeft;
	BackTransform_.Pivot_ = D3DXVECTOR2(0, 1);
	BackTransform_.Width_ = parent->Width_ / 2 - 20;
	BackTransform_.Height_ = 122;

	IconBackImage_.Load("Image/Test.png");
	IconBackImage_.SetTransform(&IconBackTransform_);
	IconBackTransform_.Parent_ = &BackTransform_;
	IconBackTransform_.Anchor_ = RectTransform::MiddleLeft;
	IconBackTransform_.Pivot_.x = 0;
	IconBackTransform_.Width_ = 60;
	IconBackTransform_.Height_ = 115;
	IconBackTransform_.Position_.x = 5;

	NameText_.Create(10, 10);
	NameText_.SetTransform(&NameTransform_);
	NameText_.SetFormat(Text::Left);
	NameTransform_.Parent_ = &IconBackTransform_;
	NameTransform_.Anchor_ = RectTransform::TopRight;
	NameTransform_.Position_.x = 5;

	IconImage_.Load();
	IconImage_.SetTransform(&IconTransform_);
	IconTransform_.Parent_ = &IconBackTransform_;
	IconTransform_.Width_ = 50;
	IconTransform_.Height_ = 50;

	{//�p�����[�^�\���p�e�L�X�g
		ParameterText_.Create(25, 25);
		ParameterText_.SetTransform(&ParameterTransform_);
		//ParameterText_.SetColor(D3DXVECTOR4(255, 255, 255, 255));
		ParameterText_.SetFormat(Text::Left);
		ParameterTransform_.Parent_ = &BackTransform_;
		ParameterTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomLeft;
		ParameterTransform_.Position_ = D3DXVECTOR3(70,-30,0);
	}
	{
		ParamNameText_.Create(10, 10);
		ParamNameText_.SetTransform(&ParamNameTransform_);
		ParamNameText_.SetFormat(Text::Left);
		ParamNameTransform_.Parent_ = &BackTransform_;
		ParamNameTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomRight;
		ParamNameTransform_.Position_ = D3DXVECTOR3(-70, -15, 0);
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
		IconImage_.Load(item->GetIconFilePath());
		IconImage_.Render();
		NameText_.Render(item->GetName());

		int par = item->GetParameter();

		if (par >= 0)
		{
			char text[10];
			sprintf_s(text, "%d", par);
			char Name[10] = "";
			switch (item->GetItemType())
			{
			case Sword:
				strcat(Name, "�U����");
				break;
			case Shield:
			case Helm:
			case Armor:
			case Arm:
			case Greaves:
				strcat(Name, "�h���");
				break;
			default:
				break;
			}
			ParameterText_.Render(text);
			ParamNameText_.Render(Name);
		}
	}
}