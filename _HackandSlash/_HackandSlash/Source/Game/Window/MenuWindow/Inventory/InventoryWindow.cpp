/**
* ���j���[�E�B���h�E�̃C���x���g���E�B���h�E�N���X�̎���.
*/
#include"stdafx.h"
#include"InventoryWindow.h"

/**
* ������.
*/
void InventoryWindow::Start(RectTransform * rt, float namepos)
{
	State_ = StateE::Select;

	NameStart(rt, "Image/Inventory.png", namepos,283);

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

		//��������]���Ă��Ȃ�
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

	IconImage_[4].Load("Icon/Sword.png");		//��
	IconImage_[3].Load("Icon/Shield.png");		//��
	IconImage_[2].Load("Icon/Helm.png");		//��
	IconImage_[1].Load("Icon/Armor.png");		//��
	IconImage_[0].Load("Icon/Arm.png");			//�r
	IconImage_[7].Load("Icon/Greaves.png");		//�r
	IconImage_[6].Load("Icon/Accessory.png");	//�A�N�Z
	IconImage_[5].Load("Icon/Accessory.png");	//�A�N�Z

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

	//�����A�C�e���̏ڍו\���E�B���h�E�̏�����
	for (int i = 0; i < 4; i++)
	{
		float posy = i * -126 - 80;
		ItemDetailRender_[i].Start(&DetailTransform_, Vector3(0, posy, 0));
	}

	{//�ڍׂ�Select���Ă���\���p�摜�̏�����
		DetailSelectImage_.Load("Image/SelectItem.png");
		DetailSelectImage_.SetTransform(&DetailSelectTransform_);
		DetailSelectTransform_.Parent_ = ItemDetailRender_[0].GetTransform();
		DetailSelectTransform_.Width_ = DetailSelectTransform_.Parent_->Width_ + 2;
		DetailSelectTransform_.Height_ = DetailSelectTransform_.Parent_->Height_ + 5;
	}
	
	EquipmentDetailRender_.Start(&DetailTransform_);

	{//�����i�e�L�X�g�̏�����
		ShojiText_.Create(15, 15);
		ShojiText_.SetTransform(&ShojiTransform_);
		ShojiTransform_.Parent_ = &DetailTransform_;
		ShojiTransform_.Anchor_ = AnchorPresetE::TopCenter;
		ShojiTransform_.Position_ = Vector3(-130, 65, 0);
	}

	{//�����i�e�L�X�g�̏�����
		SoubiText_.Create(15, 15);
		SoubiText_.SetTransform(&SoubiTransform_);
		SoubiTransform_.Parent_ = &DetailTransform_;
		SoubiTransform_.Anchor_ = AnchorPresetE::TopCenter;
		SoubiTransform_.Position_ = Vector3(130, 65, 0);
	}

}

/**
* �X�V.
*/
void InventoryWindow::Update()
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

			//���ݑI�����Ă��Ȃ����.
			if (SelectEquipment_ != (ItemTypeE)num)
			{
				SoundSource* se = NewGO<SoundSource>();
				se->InitOnMemory("Game/Select");
				se->Play();

				SelectEquipment_ = (ItemTypeE)num;
			}
		}
		
		if (XInput().IsTrigger(ButtonE::A))
		{
			//A�{�^���������ꂽ.
			if (InventoryManager().GetItemSize(SelectEquipmentCode[SelectEquipment_]) > 0)
			{
				DetailSelectTransform_.Parent_ = ItemDetailRender_[NowSelect_[SelectEquipment_]].GetTransform();
				DetailSelectTransform_.Update();

				//��ԑJ��.
				ChangeState(StateE::Detail);

				//����
				SoundSource* se = NewGO<SoundSource>();
				se->InitOnMemory("Common/SelectChange");
				se->Play();

				break;
			}
		}

	}
	break;
	case StateE::Detail:
	{

		//�O�t���[���̌��ʂ���.
		BefSelect_[SelectEquipment_] = NowSelect_[SelectEquipment_];

		static bool flag[2] ={ false,false };

		bool isSound = false;

		if (XInput().GetLeftStick().y > 0)
		{
			//��ɃX���C�h
			if (!flag[0])
			{
				if (NowSelect_[SelectEquipment_] <= 0)
				{
					//���E�܂ŕ\��
					if (LeadIdx[SelectEquipment_] > 0)
					{
						LeadIdx[SelectEquipment_]--;

						isSound = true;
					}
					
				}

				//���ɑI������ӏ�.
				int nextselect = NowSelect_[SelectEquipment_] - 1;

				//0�𒴂��Ȃ��悤�ɂ���.
				if (nextselect < 0)
				{
					nextselect = 0;
				}
				else
				{
					isSound = true;
				}

				NowSelect_[SelectEquipment_] = nextselect;

				//�A���ŏ�ւ�����Ȃ��ݒ�.
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

				//��������.
				int limit = InventoryManager().GetItemSize(SelectEquipmentCode[SelectEquipment_]);
				
				//����������\�����鐔������������.
				int num = limit - MAX_DISPLAY;

				if (NowSelect_[SelectEquipment_] >= MAX_DISPLAY - 1)
				{
					if (LeadIdx[SelectEquipment_] < num)
					{
						LeadIdx[SelectEquipment_]++;

						isSound = true;
					}
				}

				//���̑I���ӏ�.
				int nextselect = NowSelect_[SelectEquipment_] + 1;
				
				//�\�����𒴂��Ȃ��悤�ɂ���.
				if (MAX_DISPLAY - 1 < nextselect)
				{
					nextselect = MAX_DISPLAY - 1;
				}
				else
				{
					isSound = true;
				}
				
				NowSelect_[SelectEquipment_] = nextselect;

				//�A���ŏ�ւ�����Ȃ��ݒ�.
				flag[1] = true;
			}
		}
		else
		{
			flag[1] = false;
		}

		if (BefSelect_[SelectEquipment_] != NowSelect_[SelectEquipment_])
		{
			//�I�����ς���Ă���̂Őe��ύX.
			DetailSelectTransform_.Parent_ = ItemDetailRender_[NowSelect_[SelectEquipment_]].GetTransform();
		}

		DetailSelectTransform_.Update();

		if (isSound)
		{
			//���������t���O��true.

			SoundSource* se = NewGO<SoundSource>();
			se->InitOnMemory("Game/Select");
			se->Play();
		}

		if (XInput().IsTrigger(ButtonE::A))
		{
			//A�{�^���������ꂽ.

			ChangeItem();
		}

		if (XInput().IsTrigger(ButtonE::B))
		{
			//B�{�^���������ꂽ.

			//��ԑJ��.
			ChangeState(StateE::Select);

			//����
			SoundSource* se = NewGO<SoundSource>();
			se->InitOnMemory("Common/SelectChange");
			se->Play();

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

		//�I������Ă�����傫��.
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

		//�A�C�e�����������Ă��Ȃ����������Ă��Ȃ�.
		if (InventoryManager().GetItemSize(SelectEquipmentCode[i]) <= 0 && !Player_->GetIsItemSet(SelectEquipmentCode[i]))
		{
			//���m�N���ɐݒ�.
			IconImage_[i].SetMonochrome(true);
		}
		else
		{
			IconImage_[i].SetMonochrome(false);
		}

		//�g�����X�t�H�[���̍X�V.
		IconTransform_[i].Update();

	}

	SelectNameTransform_.Update();

	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		ItemDetailRender_[i].Update();
	}

	EquipmentDetailRender_.Update();

	{//�e�L�X�g�̍X�V
		ShojiTransform_.Update();
		SoubiTransform_.Update();
	}
}

/**
* �`��.
*/
void InventoryWindow::Render()
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

	for (int i = 0; i < MAX_DISPLAY; i++)
	{
		EquipmentItem* item = InventoryManager().GetItem(SelectEquipmentCode[SelectEquipment_], i + LeadIdx[SelectEquipment_]);
		ItemDetailRender_[i].Render(item);
	}

	EquipmentDetailRender_.Render(Player_->GetEquipmentItem(SelectEquipmentCode[SelectEquipment_]));

	{//�e�L�X�g�̕\��
		ShojiText_.Render("�����i");
		SoubiText_.Render("�����i");
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

/**
* �A�C�e��������.
*/
void InventoryWindow::ChangeItem()
{

	int select = NowSelect_[SelectEquipment_] + LeadIdx[SelectEquipment_];

	//���ݑ������Ă���A�C�e�����擾
	EquipmentItem* item = Player_->GetEquipmentItem(SelectEquipmentCode[SelectEquipment_]);

	//����ւ���A�C�e�����擾
	EquipmentItem* ret = InventoryManager().ChangeItem(SelectEquipmentCode[SelectEquipment_],item, select);

	//�ݒ�
	Player_->SetEquipmentItem(ret);

	SoundSource* se = NewGO<SoundSource>();
	se->InitOnMemory("Game/Equipment");
	se->Play();
}