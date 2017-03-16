/**
* フェードクラスの実装.
*/
#include"stdafx.h"
#include"Fade.h"

/**
* 初期化.
*/
void Fade::Start()
{
	FadeImage_.Load("Image/FadeImage.png");
	FadeImage_.SetTransform(&FadeTransform_);

	//大きさをフルスクリーンに設定.
	FadeTransform_.Width_ = Engine().GetScreenW();
	FadeTransform_.Height_ = Engine().GetScreenH();

}

/**
* 更新.
*/
void Fade::Update()
{
	switch (State_)
	{
	case FadeIn:
		if (FadeNowAlpha_ > 0)
		{
			//フェードが明けきってないので値を更新.
			FadeNowAlpha_ -= FadeSpeed_ * Time().DeltaTime();
		}
		else
		{
			//フェードが明けきった.
			State_ = FadeCompletion;
		}
		break;
	case FadeOut:
		if (FadeNowAlpha_ < 1)
		{
			//フェードがかかりきっていないので値を更新.
			FadeNowAlpha_ += FadeSpeed_ * Time().DeltaTime();
		}
		else
		{
			//フェードがかかりきった.
			State_ = FadeCompletion;
		}
		break;
	case FadeCompletion:
		break;
	default:
		break;
	}

	//トランスフォームの更新
	FadeTransform_.Update();

	FadeImage_.Color_.w = FadeNowAlpha_;

}

/**
* ポストエフェクト後の描画.
*/
void Fade::PostRender()
{
	FadeImage_.Render();
}
