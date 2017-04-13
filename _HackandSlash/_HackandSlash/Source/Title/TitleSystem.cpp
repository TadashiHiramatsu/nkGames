/**
 * @file Source\Title\GUI\TitleSystem.cpp
 *
 * タイトルシステムクラスの実装.
 */
#include"stdafx.h"
#include"TitleSystem.h"

#include"GUI\TitleSelect\TitleSelect_NewGame.h"
#include"GUI\TitleSelect\TitleSelect_Continue.h"
#include"GUI\TitleSelect\TitleSelect_Exit.h"

 /**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::Start()
{
	//背景作成
	NewGO<TitleBack>(0);

	TitleName_ = NewGO<TitleName>();

	//フェード作成
	Fade_ = NewGO<Fade>(2);
	Fade_->StartFadeIn();

	InitSelect();

	CursorImage_.Load("Image/SelectCursor.png");
	CursorImage_.SetTransform(&CursorRT_);

	CursorRT_.Width_ = 69 / 2.5f;
	CursorRT_.Height_ = 71 / 2.5f;
	CursorRT_.Pivot_ = Vector2(1, 0.5f);
	CursorRT_.Anchor_ = AnchorPresetE::MiddleLeft;
	CursorRT_.Position_.x = -10;

	//BGM読み込み.
	TitleBGM_ = NewGO<SoundSource>();
	TitleBGM_->InitStreaming("Title/TitleBGM");
	TitleBGM_->Play(true);

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::Update()
{
	if (TitleName_->IsFade())
	{
		//ゲーム名表示のフェードが終了.

		if (!isDecision_)
		{
			//決定状態でない.

			if (CursorUpDownMove())
			{
				CursorRT_.Parent_ = &SelectList_[NowSelect_]->GetRectTransform();

				//カーソル音再生.
				SoundSource* sound = NewGO<SoundSource>();
				sound->InitOnMemory("Common/SelectChange");
				sound->Play();
			}

			if (XInput().IsTrigger(ButtonE::A))
			{
				//Aボタンを押された.

				isDecision_ = true;

				//決定音再生.
				SoundSource* sound = NewGO<SoundSource>();
				sound->InitStreaming("Title/GameStart");
				sound->Play();

				//BGMストップ.
				TitleBGM_->Stop();

				//フェードアウト開始.
				Fade_->StartFadeOut();
			}
		}
		else
		{
			//決定状態.

			if (Fade_->GetState() == Fade::FadeStateE::FadeCompletion)
			{
				//フェードが終了したのでセレクト内容を実行. 
				bool is = SelectList_[(int)NowSelect_]->OnTrigger();
				if (!is)
				{
					isDecision_ = false;
					Fade_->StartFadeIn();
					TitleBGM_->Play(true);
				}
			}
		}
	}

	CursorRT_.Update();
}

/**
* ポストエフェクト後の描画.
*/
void TitleSystem::PostRender()
{
	CursorImage_.Render();
}

/**
* セレクトの初期化.
*/
void TitleSystem::InitSelect()
{
	//ニューゲーム
	SelectList_[(int)SelectStateE::NewGame] = NewGO<TitleSelect_NewGame>();
	//コンティニュー
	SelectList_[(int)SelectStateE::Continue] = NewGO<TitleSelect_Continue>();
	//エグジット
	SelectList_[(int)SelectStateE::Exit] = NewGO<TitleSelect_Exit>();

	NowSelect_ = (int)SelectStateE::NewGame;

	CursorRT_.Parent_ = &SelectList_[NowSelect_]->GetRectTransform();
}

/**
* カーソルの上下移動.
*/
bool TitleSystem::CursorUpDownMove()
{
	//連打できないようにする.
	static bool isTrigger = false;

	if (!isTrigger)
	{
		//前フレームに押されていない.

		if (XInput().GetLeftStick().y >= 0.1f)
		{
			//上に移動.
			if (NowSelect_ == (int)SelectStateE::StateBegin)
			{
				NowSelect_ = (int)SelectStateE::StateEnd;
			}
			else
			{
				NowSelect_--;
			}
			isTrigger = true;

			return true;
		}
		if (XInput().GetLeftStick().y <= -0.1f)
		{
			//下に移動.
			if (NowSelect_ == (int)SelectStateE::StateEnd)
			{
				NowSelect_ = (int)SelectStateE::StateBegin;
			}
			else
			{
				NowSelect_++;
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
}
