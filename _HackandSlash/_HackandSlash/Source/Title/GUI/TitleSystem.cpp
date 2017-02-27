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
	TitleBack_ = NewGO<TitleBack>(0);

	//タイトルネーム画像の初期化
	TitleNameImage_.Load("Image/NonTitle.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV初期化
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;
	
	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 150;
	TitleNameRT_.Position_ = D3DXVECTOR3(250, 200, 0);

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
	NewGameRT_.Position_ = D3DXVECTOR3(300, -100,0);
	ContinueRT_.Position_ = D3DXVECTOR3(300, -200,0);

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
	case TitleSystem::StartUp:
	{
		//RectUVを取得
		D3DXVECTOR4 rectUV = TitleNameImage_.RectUV_;

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
			State_ = Run;
			break;
		}
	}
	break;
	case TitleSystem::Run:
	{
		if (XInput().IsTrigger(ButtonE::ButtonA))
		{
			//エンターキーを押された
			State_ = BlackOut;
		}
	}
	break;
	case TitleSystem::BlackOut:
	{
		//徐々に暗く
		BlackOutColor_ = fmax(0.0f, BlackOutColor_ - 0.01f);

		//色を作成
		D3DXVECTOR4 color = D3DXVECTOR4(BlackOutColor_, BlackOutColor_, BlackOutColor_, 1.0f);
		TitleNameImage_.Color_ = color;
		NewGameImage_.Color_ = color;
		ContinueImage_.Color_ = color;
		TitleBack_->SetColor(color);

		//ブラックアウト終了
		if (BlackOutColor_ <= 0.0f)
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