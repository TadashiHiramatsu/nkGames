/**
 * @file Source\Title\GUI\TitleSystem.cpp
 *
 * タイトルシステムクラスの実装.
 */
#include"stdafx.h"
#include"TitleSystem.h"

#include"../../Game/GameScene.h"

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

	//フェード作成
	Fade_ = NewGO<Fade>(2);

	//タイトルネーム画像の初期化
	TitleNameImage_.Load("Image/NonTitle.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV初期化
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;
	
	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 150;
	TitleNameRT_.Position_ = Vector3(250, 200, 0);

	//ニューゲーム画像の初期化
	NewGameImage_.Load("Image/NewGame.png");
	NewGameImage_.SetTransform(&NewGameRT_);

	//コンティニュー画像の初期化
	ContinueImage_.Load("Image/Continue.png");
	ContinueImage_.SetTransform(&ContinueRT_);

	//横幅を設定
	NewGameRT_.Width_ = ContinueRT_.Width_ = 320;
	NewGameRT_.Height_ = ContinueRT_.Height_ = 80;

	//位置を設定
	NewGameRT_.Position_ = Vector3(300, -100,0);
	ContinueRT_.Position_ = Vector3(300, -200,0);

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
	switch (State_)
	{
	case TitleStateE::StartUp:
	{
		//RectUVを取得
		Vector4 rectUV = TitleNameImage_.RectUV_;

		//起動タイム
		static float StartTime = 2.0f;
		//起動ローカルタイム
		static float StartUpLT = 0.0f;
		
		StartUpLT += Time().DeltaTime();
		if (StartUpLT >= StartTime)
		{
			//UVを完全表示にずらしていく
			rectUV.x = fmax(0.0f, rectUV.x - 0.005f);
			rectUV.z = fmin(1.0f, rectUV.z + 0.005f);
			//サイズを調整
			float a = 1 - rectUV.x * 2;
			TitleNameRT_.Width_ = 600 * a;
		}

		//RectUVを設定
		TitleNameImage_.RectUV_ = rectUV;
		
		if (rectUV.x <= 0.0f)
		{
			//完全に表示されたのでRun状態に変化
			State_ = TitleStateE::Run;
			break;
		}
	}
	break;
	case TitleStateE::Run:
	{
		if (XInput().IsTrigger(ButtonE::A))
		{
			//Aボタンを押された.

			//ブラックアウト状態に変化.
			State_ = TitleStateE::BlackOut;
			//フェードアウト開始.
			Fade_->StartFadeOut();

			//BGMストップ.
			TitleBGM_->Stop();

			//決定音再生.
			SoundSource* sound = NewGO<SoundSource>();
			sound->InitStreaming("Title/GameStart");
			sound->Play();

		}
	}
	break;
	case TitleStateE::BlackOut:
	{
		//フェードアウト終了
		if (Fade_->GetState() == Fade::FadeCompletion)
		{
			//ゲームシーンに変更
			SceneManager().ChangeScene<GameScene>();
			return;
		}
	}
	break;
	default:
		break;
	}

	//トランスフォームの更新
	TitleNameRT_.Update();
	NewGameRT_.Update();
	ContinueRT_.Update();
}

/**
 * ポストエフェクト後の描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::PostRender()
{
	TitleNameImage_.Render();
	NewGameImage_.Render();
	//ContinueImage_.Render();
}