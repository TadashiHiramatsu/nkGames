/**
* タイトルシーンのゲームタイトル表示クラスの実装.
*/
#include"stdafx.h"
#include"TitleName.h"

/**
* 初期化.
*/
void TitleName::Start()
{
	//タイトルネーム画像の初期化
	TitleNameImage_.Load("Image/non_title.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV初期化
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;

	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 73 * 1.5;
	TitleNameRT_.Position_ = Vector3(250, 200, 0);

	//フェード速度の設定.
	FadeSpeed = 3.0f;
}

/**
* 更新.
*/
void TitleName::Update()
{
	if (!isFade_)
	{
		//RectUVを取得
		Vector4 rectUV = TitleNameImage_.RectUV_;

		//起動タイム
		static float StartTime = 2.0f;
		//起動ローカルタイム
		static float StartLT = 0.0f;

		StartLT += Time().DeltaTime();
		if (StartLT >= StartTime)
		{
			//UVを完全表示にずらしていく

			//2秒かけて表示する.
			float speed = 1 / FadeSpeed * Time().DeltaTime();

			rectUV.x = fmax(0.0f, rectUV.x - speed);
			rectUV.z = fmin(1.0f, rectUV.z + speed);

			//サイズを調整
			float a = 1 - rectUV.x * 2;
			TitleNameRT_.Width_ = 396 * 1.5 * a;
		}

		//RectUVを設定
		TitleNameImage_.RectUV_ = rectUV;

		if (rectUV.x <= 0.0001f)
		{
			isFade_ = true;
		}
	}

	//トランスフォームの更新.
	TitleNameRT_.Update();
}

/**
* ポストエフェクト後の描画.
*/
void TitleName::PostRender()
{
	TitleNameImage_.Render();
}
