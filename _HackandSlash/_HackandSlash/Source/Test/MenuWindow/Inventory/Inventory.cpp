#include"stdafx.h"
#include"Inventory.h"

#include"../../Item/InventoryManager.h"

void Inventory::Start(RectTransform * rt, float namepos)
{
	State_ = StateE::Select;

	NameStart(rt, "Image/Inventory.png", namepos);

	{//�I���E�B���h�E�摜�̏�����
		ChoiceImage_.Load("Image/Test.png");
		ChoiceImage_.SetTransform(&ChoiceTransform_);
		ChoiceTransform_.Parent_ = rt;
		ChoiceTransform_.Width_ = 280;
		ChoiceTransform_.Height_ = 600;
		ChoiceTransform_.Position_.x = -280;
		ChoiceTransform_.Pivot_.y = 1;
	}

	{//�ڍ׃E�B���h�E�摜�̏�����
		DetailImage_.Load("Image/Test.png");
		DetailImage_.SetTransform(&DetailTransform_);
		DetailTransform_.Parent_ = rt;
		DetailTransform_.Width_ = 540;
		DetailTransform_.Height_ = 600;
		DetailTransform_.Position_.x = 150;
		DetailTransform_.Pivot_.y = 1;
	}

	{//�A�C�R���\�����邽�߂̒��S�n��������
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

		//��������]���Ă��Ȃ�
		IconBackTransform_[i].Parent_ = &MiddleTransform_[i % 2];

		if (i % 2 == 1)
		{
			IconBackTransform_[i].RotationZ(-45);
		}

		IconBackTransform_[i].Width_ = 60;
		IconBackTransform_[i].Height_ = 60;
		IconBackTransform_[i].Position_ = pos[i / 2];

	}

	IconImage_[0].Load("Icon/Arm.png");		//�r
	IconImage_[1].Load("Icon/Armor.png");		//��
	IconImage_[2].Load("Icon/Helm.png");		//��
	IconImage_[3].Load("Icon/Shield.png");		//��
	IconImage_[4].Load("Icon/Sword.png");		//��
	IconImage_[5].Load("Icon/Accessory.png");	//�A�N�Z
	IconImage_[6].Load("Icon/Accessory.png");	//�A�N�Z
	IconImage_[7].Load("Icon/Greaves.png");			//�r

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
	SelectNameTransform_.Anchor_ = RectTransform::AnchorPresetE::TopCenter;
	SelectNameTransform_.Position_.y = 30;

	for (int i = 0; i < 4; i++)
	{
		float posy = i * -130 - 70;
		ItemDetailRender_[i].Start(&DetailTransform_, D3DXVECTOR3(0, posy, 0));
	}

	{//�ڍׂ�Select���Ă���\���p�摜�̏�����
		DetailSelectImage_.Load("Image/SelectItem.png");
		DetailSelectImage_.SetTransform(&DetailSelectTransform_);
		DetailSelectTransform_.Parent_ = ItemDetailRender_[0].GetTransform();
		DetailSelectTransform_.Width_ = DetailSelectTransform_.Parent_->Width_ + 5;
		DetailSelectTransform_.Height_ = DetailSelectTransform_.Parent_->Height_ + 5;
	}

}

void Inventory::Update()
{
	switch (State_)
	{
	case Inventory::Select:
	{

		D3DXVECTOR2 LeftStick = XInput().GetLeftStick();
		if (D3DXVec2Length(&LeftStick) > 0.0f)
		{
			float angle = XInput().GetLeftStickAngle();
			SelectEquipment_ = (int)angle / (360 / MAX_EQUIPMENT);
		}

		if (XInput().IsTrigger(ButtonE::ButtonA))
		{
			//A�{�^���������ꂽ�̂ŏڍ׏�Ԃɕω�.
			ChangeState(StateE::Detail);
			break;
		}

	}
	break;
	case Inventory::Detail:
	{
		BefSelect_ = NowSelect_;

		static bool flag[2] =
		{ false,false };

		if (XInput().GetLeftStick().y > 0)
		{
			//��
			if (!flag[0])
			{

				if (NowSelect_ <= 0)
				{
					LeadIdx[SelectEquipment_]--;
					
					//���E�܂ŕ\��
					if (LeadIdx[SelectEquipment_] < 0)
					{
						LeadIdx[SelectEquipment_] = 0;
					}
				}

				NowSelect_ = max(0, NowSelect_ - 1);

				flag[0] = true;
			}
		}
		else
		{
			flag[0] = false;
		}

		if (XInput().GetLeftStick().y < 0)
		{
			//��
			if (!flag[1])
			{

				if (NowSelect_ >= MAX_DISPLAY - 1)
				{
					LeadIdx[SelectEquipment_]++;

					CInventoryManager::ItemTypeE SelectNumber[8] =
					{
						CInventoryManager::Arm,			//�r
						CInventoryManager::Armor,		//��
						CInventoryManager::Helm,		//��
						CInventoryManager::Shield,		//��
						CInventoryManager::Sword,		//��
						CInventoryManager::Accessory,	//�A�N�Z�T���[
						CInventoryManager::Accessory,	//�A�N�Z�T���[
						CInventoryManager::Greaves		//�r
					};

					//���E�܂ŕ\��
					int limit = InventoryManager().GetItemSize(SelectNumber[SelectEquipment_]);
					limit -= MAX_DISPLAY;

					if (LeadIdx[SelectEquipment_] > limit)
					{
						LeadIdx[SelectEquipment_] = limit;
					}
				}

				NowSelect_ = min(MAX_DISPLAY - 1, NowSelect_ + 1);

				flag[1] = true;
			}
		}
		else
		{
			flag[1] = false;
		}

		if (BefSelect_ != NowSelect_)
		{
			DetailSelectTransform_.Parent_ = ItemDetailRender_[NowSelect_].GetTransform();
		}

		DetailSelectTransform_.Update();

		if (XInput().IsTrigger(ButtonE::ButtonB))
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

	SelectNameTransform_.Update();

	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		ItemDetailRender_[i].Update();
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
		"�A�[��",
		"�A�[�}�[",
		"�w����",
		"�V�[���h",
		"�\�[�h",
		"�A�N�Z�T���[",
		"�A�N�Z�T���[",
		"�O���[��",
	};
	SelectName_.Render(Name[SelectEquipment_]);

	CInventoryManager::ItemTypeE SelectNumber[8] =
	{
		CInventoryManager::Arm,			//�r
		CInventoryManager::Armor,		//��
		CInventoryManager::Helm,		//��
		CInventoryManager::Shield,		//��
		CInventoryManager::Sword,		//��
		CInventoryManager::Accessory,	//�A�N�Z�T���[
		CInventoryManager::Accessory,	//�A�N�Z�T���[
		CInventoryManager::Greaves		//�r
	};
	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		IItemData* item = InventoryManager().GetItem(SelectNumber[SelectEquipment_], i + LeadIdx[SelectEquipment_]);
		ItemDetailRender_[i].Render(item);
	}

	switch (State_)
	{
	case Inventory::Select:
	{
	}
	break;
	case Inventory::Detail:
	{
		DetailSelectImage_.Render();
	}
	break;
	default:
		break;
	}

}
