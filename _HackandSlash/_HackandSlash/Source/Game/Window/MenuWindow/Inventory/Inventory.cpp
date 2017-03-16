#include"stdafx.h"
#include"Inventory.h"

void Inventory::Start(RectTransform * rt, float namepos)
{
	State_ = StateE::Select;

	NameStart(rt, "Image/Inventory.png", namepos);

	{//選択ウィンドウ画像の初期化
		ChoiceImage_.Load("Image/Test.png");
		ChoiceImage_.SetTransform(&ChoiceTransform_);
		ChoiceTransform_.Parent_ = rt;
		ChoiceTransform_.Width_ = 280;
		ChoiceTransform_.Height_ = 600;
		ChoiceTransform_.Position_.x = -280;
		ChoiceTransform_.Pivot_.y = 1;
	}

	{//詳細ウィンドウ画像の初期化
		DetailImage_.Load("Image/Test.png");
		DetailImage_.SetTransform(&DetailTransform_);
		DetailTransform_.Parent_ = rt;
		DetailTransform_.Width_ = 540;
		DetailTransform_.Height_ = 600;
		DetailTransform_.Position_.x = 150;
		DetailTransform_.Pivot_.y = 1;
	}

	{//アイコン表示するための中心地を初期化
		MiddleImage_.Load("Image/Middle.png");
		MiddleImage_.SetTransform(&MiddleTransform_[0]);
		MiddleTransform_[0].Parent_ = &ChoiceTransform_;
		MiddleTransform_[0].Position_.y = 130;
		MiddleTransform_[0].Width_ = 250;
		MiddleTransform_[0].Height_ = 250;
		MiddleTransform_[1].Parent_ = &ChoiceTransform_;
		MiddleTransform_[1].Position_.y = 130;
		MiddleTransform_[1].RotationZ(45);
	}

	float fpos = 110;
	Vector3 pos[4] =
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

		BefSelect_[i] = NowSelect_[i] = 0;

	}

	IconImage_[4].Load("Icon/Sword.png");		//剣
	IconImage_[3].Load("Icon/Shield.png");		//盾
	IconImage_[2].Load("Icon/Helm.png");		//頭
	IconImage_[1].Load("Icon/Armor.png");		//胴
	IconImage_[0].Load("Icon/Arm.png");			//腕
	IconImage_[7].Load("Icon/Greaves.png");		//脚
	IconImage_[6].Load("Icon/Accessory.png");	//アクセ
	IconImage_[5].Load("Icon/Accessory.png");	//アクセ

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconImage_[i].SetTransform(&IconTransform_[i]);

		IconTransform_[i].Parent_ = &IconBackTransform_[i];

		IconTransform_[i].Width_ = DefaultIconSize_;
		IconTransform_[i].Height_ = DefaultIconSize_;

		LeadIdx[i] = 0;
	}

	SelectName_.Create(20, 20);
	SelectName_.SetTransform(&SelectNameTransform_);
	SelectNameTransform_.Parent_ = &DetailTransform_;
	SelectNameTransform_.Anchor_ = AnchorPresetE::TopCenter;
	SelectNameTransform_.Position_.y = 30;

	//所持アイテムの詳細表示ウィンドウの初期化
	for (int i = 0; i < 4; i++)
	{
		float posy = i * -126 - 80;
		ItemDetailRender_[i].Start(&DetailTransform_, Vector3(0, posy, 0));
	}

	{//詳細をSelectしている表示用画像の初期化
		DetailSelectImage_.Load("Image/SelectItem.png");
		DetailSelectImage_.SetTransform(&DetailSelectTransform_);
		DetailSelectTransform_.Parent_ = ItemDetailRender_[0].GetTransform();
		DetailSelectTransform_.Width_ = DetailSelectTransform_.Parent_->Width_ + 2;
		DetailSelectTransform_.Height_ = DetailSelectTransform_.Parent_->Height_ + 5;
	}
	
	EquipmentDetailRender_.Start(&DetailTransform_);

	{//所持品テキストの初期化
		ShojiText_.Create(15, 15);
		ShojiText_.SetTransform(&ShojiTransform_);
		ShojiTransform_.Parent_ = &DetailTransform_;
		ShojiTransform_.Anchor_ = AnchorPresetE::TopCenter;
		ShojiTransform_.Position_ = Vector3(-130, 65, 0);
	}

	{//所持品テキストの初期化
		SoubiText_.Create(15, 15);
		SoubiText_.SetTransform(&SoubiTransform_);
		SoubiTransform_.Parent_ = &DetailTransform_;
		SoubiTransform_.Anchor_ = AnchorPresetE::TopCenter;
		SoubiTransform_.Position_ = Vector3(130, 65, 0);
	}

}

void Inventory::Update()
{
	switch (State_)
	{
	case StateE::Select:
	{

		float Len = XInput().GetLeftStick().Length();
		if (Len > 0.8f)
		{
			int angle = XInput().GetLeftStickAngle() + (360 / MAX_EQUIPMENT / 2);
			int num = (angle / (360 / MAX_EQUIPMENT)) % MAX_EQUIPMENT;
			SelectEquipment_ = (ItemTypeE)num;
		}

		if (XInput().IsTrigger(ButtonE::A))
		{
			//Aボタンが押された.
			if (InventoryManager().GetItemSize(SelectEquipmentCode[SelectEquipment_]) > 0)
			{
				DetailSelectTransform_.Parent_ = ItemDetailRender_[NowSelect_[SelectEquipment_]].GetTransform();
				DetailSelectTransform_.Update();
				ChangeState(StateE::Detail);
				break;
			}
		}

	}
	break;
	case StateE::Detail:
	{

		//前フレームの結果を代入.
		BefSelect_[SelectEquipment_] = NowSelect_[SelectEquipment_];

		static bool flag[2] =
		{ false,false };

		if (XInput().GetLeftStick().y > 0)
		{
			//上
			if (!flag[0])
			{

				if (NowSelect_[SelectEquipment_] <= 0)
				{
					LeadIdx[SelectEquipment_]--;

					//限界まで表示
					if (LeadIdx[SelectEquipment_] < 0)
					{
						LeadIdx[SelectEquipment_] = 0;
					}
				}

				NowSelect_[SelectEquipment_] = max(0, NowSelect_[SelectEquipment_] - 1);

				flag[0] = true;
			}
		}
		else
		{
			flag[0] = false;
		}

		if (XInput().GetLeftStick().y < 0)
		{
			//下
			if (!flag[1])
			{

				int limit = InventoryManager().GetItemSize(SelectEquipmentCode[SelectEquipment_]);
				int num = limit - MAX_DISPLAY;

				if (NowSelect_[SelectEquipment_] >= MAX_DISPLAY - 1)
				{
					LeadIdx[SelectEquipment_]++;

					if (LeadIdx[SelectEquipment_] > num)
					{
						LeadIdx[SelectEquipment_] = num;
					}
				}
				else
				{
					NowSelect_[SelectEquipment_] = min(MAX_DISPLAY - 1 + num, NowSelect_[SelectEquipment_] + 1);
				}

				flag[1] = true;
			}
		}
		else
		{
			flag[1] = false;
		}

		if (BefSelect_[SelectEquipment_] != NowSelect_[SelectEquipment_])
		{
			DetailSelectTransform_.Parent_ = ItemDetailRender_[NowSelect_[SelectEquipment_]].GetTransform();
		}

		DetailSelectTransform_.Update();

		if (XInput().IsTrigger(ButtonE::A))
		{
			ChangeItem();
		}

		if (XInput().IsTrigger(ButtonE::B))
		{
			ChangeState(StateE::Select);
			break;
		}


	}
	break;
	default:
		break;
	}

	ChoiceTransform_.Update();
	DetailTransform_.Update();

	MiddleTransform_[0].Update();
	MiddleTransform_[1].Update();

	for (int i = 0; i < MAX_EQUIPMENT; i++)
	{
		IconBackTransform_[i].Update();

		//選択されていたら大きく.
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

		//アイテムを所持していない.
		if (InventoryManager().GetItemSize(SelectEquipmentCode[i]) <= 0 && !Player_->GetIsSet(SelectEquipmentCode[i]))
		{
			//モノクロに設定.
			IconImage_[i].SetMonochrome(true);
		}
		else
		{
			IconImage_[i].SetMonochrome(false);
		}

		//トランスフォームの更新.
		IconTransform_[i].Update();

	}

	SelectNameTransform_.Update();

	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		ItemDetailRender_[i].Update();
	}

	EquipmentDetailRender_.Update();

	{//テキストの更新
		ShojiTransform_.Update();
		SoubiTransform_.Update();
	}
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

	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		EquipmentItem* item = InventoryManager().GetItem(SelectEquipmentCode[SelectEquipment_], i + LeadIdx[SelectEquipment_]);
		ItemDetailRender_[i].Render(item);
	}

	EquipmentDetailRender_.Render(Player_->GetEquipmentItem(SelectEquipmentCode[SelectEquipment_]));

	{//テキストの表示
		ShojiText_.Render("所持品");
		SoubiText_.Render("装備品");
	}

	switch (State_)
	{
	case StateE::Select:
	{
	}
	break;
	case StateE::Detail:
	{
		DetailSelectImage_.Render();
	}
	break;
	default:
		break;
	}

}

void Inventory::ChangeItem()
{

	int select = NowSelect_[SelectEquipment_] + LeadIdx[SelectEquipment_];
	
	//現在装備しているアイテムを取得
	EquipmentItem* item = Player_->GetEquipmentItem(SelectEquipmentCode[SelectEquipment_]);

	//入れ替えるアイテムを取得
	EquipmentItem* ret = InventoryManager().ChangeItem(SelectEquipmentCode[SelectEquipment_],item, select);

	//設定
	Player_->SetEquipmentItem(ret);

}
