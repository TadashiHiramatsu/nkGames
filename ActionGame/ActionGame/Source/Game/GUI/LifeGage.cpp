/**
 * @file Source\Game\GUI\LifeGage.cpp
 *
 * ライフゲージクラスの実装.
 */
#include"stdafx.h"
#include"LifeGage.h"

/**
 * コンストラクタ.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::LifeGage()
{
}

/**
 * デストラクタ.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::~LifeGage()
{
}

/**
 * 初期化.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Start()
{
	//フレームの画像をロード
	LifeFrameImage_.Load("Image/LifeFrame.png");
	//トランスフォームの設定
	LifeFrameImage_.SetTransform(&LifeFrameTransform_);

	//本体の画像をロード
	LifeImage_.Load("Image/Life.png");
	//トランスフォームの設定
	LifeImage_.SetTransform(&LifeTransform_);

	//親子関係設定
	LifeTransform_.Parent_ = &LifeFrameTransform_;

	//大きさを設定
	LifeFrameTransform_.Width_ = LifeFrameTransform_.Height_ = 150;
	LifeTransform_.Width_ = LifeTransform_.Height_ = 140;

	//フレームのアンカーを左下
	LifeFrameTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomLeft;
	LifeFrameTransform_.Pivot_ = D3DXVECTOR2(0, 0);

	//本体のアンカーをフレームの下中央
	LifeTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomCenter;
	LifeTransform_.Pivot_ = D3DXVECTOR2(0.5, 0);
	//位置を調整
	LifeTransform_.Position_.y = 5;

	//ライフのポインタを取得
	MaxLife_ = &Player_->GetParameter().MaxHp_;
	NowLife_ = &Player_->GetParameter().NowHp_;

	//フォントの初期化
	Life_.Create(20, 15);

}

/**
 * 更新.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Update()
{
	//表示領域と大きさを計算
	LifeImage_.RectUV_.y = 1.0f - (float)*NowLife_ / (float)*MaxLife_;
	LifeTransform_.Height_ = (float)*NowLife_ / (float)*MaxLife_ * 140;

	//トランスフォームの更新
	LifeFrameTransform_.Update();
	LifeTransform_.Update();

}

/**
 * ポストエフェクトの後に呼ばれる描画.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::PostRender()
{
	//画像の描画
	LifeFrameImage_.Render();
	LifeImage_.Render();

	//ライフ表示の文字列を作成
	char Now[10];
	sprintf_s(Now, "%d", *NowLife_);
	char Max[10];
	sprintf_s(Max, "%d", *MaxLife_);

	char str[30] = { 0 };
	strcat_s(str, "Life:");
	strcat_s(str, Now);
	strcat_s(str, "/");
	strcat_s(str, Max);

	//フォントを描画
	Life_.Render(str,D3DXVECTOR2(10,500));

}