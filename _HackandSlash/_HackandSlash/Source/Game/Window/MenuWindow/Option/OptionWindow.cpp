/**
* メニューウィンドウのオプションウィンドウクラスの実装.
*/
#include"stdafx.h"
#include"OptionWindow.h"

#include"../../../../Title/TitleScene.h"
#include"../../../../Common/SaveData/SaveData.h"

/**
* 初期化.
*/
void OptionWindow::Start(RectTransform * rt, float namepos)
{
	//名前表示の初期化.
	NameStart(rt, "Image/Option.png", namepos,200);

	{//選択ウィンドウ画像の初期化
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

		//サイズ設定.
		ControllerRT_.Width_ = 422;
		ControllerRT_.Height_ = 302;
	}

	for (int i = 0; i < SelectStateE::SelectNum; i++)
	{
		SelectFrameImage_[i].Load("Image/OptionFrame.png");
		SelectFrameImage_[i].SetTransform(&SelectFrameRT_[i]);

		//親を設定.
		SelectFrameRT_[i].Parent_ = &WindowRT_;

		SelectFrameRT_[i].Anchor_ = AnchorPresetE::TopLeft;

		SelectFrameRT_[i].Position_ = Vector3(200, -150 + -100 * i, 0);

		//サイズ設定.
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

		//サイズ設定.
		SelectRT_.Width_ = 180;
		SelectRT_.Height_ = 60;
	}
}

/**
* 更新.
*/
void OptionWindow::Update()
{
	
	if (SelectUpDownMove())
	{
		//移動した.

		/*SoundSource* se = NewGO<SoundSource>();
		se->InitOnMemory("Game/Menu");
		se->Play();*/

		SelectRT_.Parent_ = &SelectFrameRT_[SelectState_];
	}

	Decision();

	//更新.
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
* 描画.
*/
void OptionWindow::Render()
{
	//描画.
	WindowImage_.Render();

	ControllerImage_.Render();

	for (int i = 0; i < SelectStateE::SelectNum; i++)
	{
		SelectFrameImage_[i].Render();
	}

	OptionName_[0].Render("記録");
	OptionName_[1].Render("タイトルに戻る");
	OptionName_[2].Render("ゲームを終了");

	SelectImage_.Render();
}

/**
* 選択移動.
*/
bool OptionWindow::SelectUpDownMove()
{
	//連打できないようにする.
	static bool isTrigger = false;

	if (!isTrigger)
	{
		//前フレームに押されていない.

		if (XInput().GetLeftStick().y >= 0.1f)
		{
			//上に移動.
			if (SelectState_ != SelectStateE::SelectBegin)
			{
				SelectState_--;
			}

			isTrigger = true;

			return true;
		}
		if (XInput().GetLeftStick().y <= -0.1f)
		{
			//下に移動.
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
* 決定.
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
