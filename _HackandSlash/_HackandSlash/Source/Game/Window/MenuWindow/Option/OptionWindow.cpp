/**
* ���j���[�E�B���h�E�̃I�v�V�����E�B���h�E�N���X�̎���.
*/
#include"stdafx.h"
#include"OptionWindow.h"

#include"../../../../Title/TitleScene.h"
#include"../../../../Common/SaveData/SaveData.h"

/**
* ������.
*/
void OptionWindow::Start(RectTransform * rt, float namepos)
{
	//���O�\���̏�����.
	NameStart(rt, "Image/Option.png", namepos,200);

	{//�I���E�B���h�E�摜�̏�����
		WindowImage_.Load("Image/Test.png");
		WindowImage_.SetTransform(&WindowRT_);
		WindowRT_.Parent_ = rt;
		WindowRT_.Width_ = 850;
		WindowRT_.Height_ = 600;
		WindowRT_.Pivot_.y = 1;
	}

	{
		ControllerImage_.Load("Image/Controller.jpg");
		ControllerImage_.SetTransform(&ControllerRT_);
		ControllerRT_.Parent_ = &WindowRT_;

		ControllerRT_.Position_ = Vector3(150,50,0);

		//�T�C�Y�ݒ�.
		ControllerRT_.Width_ = 422;
		ControllerRT_.Height_ = 302;
	}

	for (int i = 0; i < SelectStateE::SelectNum; i++)
	{
		SelectFrameImage_[i].Load("Image/OptionFrame.png");
		SelectFrameImage_[i].SetTransform(&SelectFrameRT_[i]);

		//�e��ݒ�.
		SelectFrameRT_[i].Parent_ = &WindowRT_;

		SelectFrameRT_[i].Anchor_ = AnchorPresetE::TopLeft;

		SelectFrameRT_[i].Position_ = Vector3(200, -150 + -100 * i, 0);

		//�T�C�Y�ݒ�.
		SelectFrameRT_[i].Width_ = 180;
		SelectFrameRT_[i].Height_ = 60;

		OptionName_[i].Create(10, 10);
		OptionName_[i].SetTransform(&OptionNameRT_[i]);
		OptionName_[i].SetColor(Vector4(255,255,255,255));
		OptionName_[i].SetFormat(Text::FormatE::Center);

		OptionNameRT_[i].Parent_ = &SelectFrameRT_[i];

	}

	{
		SelectImage_.Load("Image/SelectItem.png");
		SelectImage_.SetTransform(&SelectRT_);

		SelectRT_.Parent_ = &SelectFrameRT_[SelectState_];

		//�T�C�Y�ݒ�.
		SelectRT_.Width_ = 180;
		SelectRT_.Height_ = 60;
	}
}

/**
* �X�V.
*/
void OptionWindow::Update()
{
	
	if (SelectUpDownMove())
	{
		//�ړ�����.

		/*SoundSource* se = NewGO<SoundSource>();
		se->InitOnMemory("Game/Menu");
		se->Play();*/

		SelectRT_.Parent_ = &SelectFrameRT_[SelectState_];
	}

	Decision();

	//�X�V.
	WindowRT_.Update();

	ControllerRT_.Update();

	for (int i = 0; i < SelectStateE::SelectNum; i++)
	{
		SelectFrameRT_[i].Update();
		OptionNameRT_[i].Update();
	}

	SelectRT_.Update();
}

/**
* �`��.
*/
void OptionWindow::Render()
{
	//�`��.
	WindowImage_.Render();

	ControllerImage_.Render();

	for (int i = 0; i < SelectStateE::SelectNum; i++)
	{
		SelectFrameImage_[i].Render();
	}

	OptionName_[0].Render("�L�^");
	OptionName_[1].Render("�^�C�g���ɖ߂�");
	OptionName_[2].Render("�Q�[�����I��");

	SelectImage_.Render();
}

/**
* �I���ړ�.
*/
bool OptionWindow::SelectUpDownMove()
{
	//�A�łł��Ȃ��悤�ɂ���.
	static bool isTrigger = false;

	if (!isTrigger)
	{
		//�O�t���[���ɉ�����Ă��Ȃ�.

		if (XInput().GetLeftStick().y >= 0.1f)
		{
			//��Ɉړ�.
			if (SelectState_ != SelectStateE::SelectBegin)
			{
				SelectState_--;
			}

			isTrigger = true;

			return true;
		}
		if (XInput().GetLeftStick().y <= -0.1f)
		{
			//���Ɉړ�.
			if (SelectState_ != SelectStateE::SelectEnd)
			{
				SelectState_++;
			}

			isTrigger = true;

			return true;
		}
	}
	else
	{
		if (XInput().GetLeftStickAngle() <= 0.0f)
		{
			isTrigger = false;
		}
	}

	return false;

	return false;
}

/**
* ����.
*/
void OptionWindow::Decision()
{
	if (XInput().IsTrigger(ButtonE::A))
	{
		switch (SelectState_)
		{
		case SelectStateE::Save:
		{
			SaveData().Save();
		}
			break;
		case SelectStateE::Title:
		{
			SceneManager().ChangeScene<TitleScene>();
		}
			break;
		case SelectStateE::Exit:
		{
			Engine().GameExit();
		}
		break;
		default:
			break;
		}
	}
}
