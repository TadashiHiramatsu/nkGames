/**
 * @file	Source\Game\GUI\ExpGage.cpp
 *
 * 経験値ゲージクラスの実装.
 */
#include"stdafx.h"
#include"ExpGage.h"

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
ExpGage::ExpGage()
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
ExpGage::~ExpGage()
{
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::Start()
{
	//フレームの画像読み込み
	ExpFrameImage_.Load("Image/ExpFrame.png");
	//トランスフォームの設定
	ExpFrameImage_.SetTransform(&ExpFrameTransform_);
	
	//本体の画像読み込み
	ExpImage_.Load("Image/Exp.png");
	//トランスフォームの設定
	ExpImage_.SetTransform(&ExpTransform_);

	//緑色に設定
	ExpImage_.Color_.x = 0.0f;
	ExpImage_.Color_.z = 0.0f;

	//親子関係設定
	ExpTransform_.Parent_ = &ExpFrameTransform_;

	//ゲージの大きさを設定
	ExpFrameTransform_.Width_ = 800;
	ExpFrameTransform_.Height_ = 20;
	ExpTransform_.Width_ = 750;
	ExpTransform_.Height_ = 10;

	//フレームのアンカーを下中央
	ExpFrameTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomCenter;
	ExpFrameTransform_.Pivot_ = D3DXVECTOR2(0.5f, 0);

	//本体のアンカーをフレームの左中央
	ExpTransform_.Anchor_ = RectTransform::AnchorPresetE::MiddleLeft;
	ExpTransform_.Pivot_ = D3DXVECTOR2(0, 0.5f);
	//少しずらす
	ExpTransform_.Position_.x = 25;

	//経験値のポインタを取得
	NextExp_ = &Player_->GetParameter().NextLevelExperience_;
	NowExp_ = &Player_->GetParameter().Experience_;

	//レベル表示フォントの作成
	Level_.Create(20, 20);
	Level_.SetTransform(&TextTransform_);
	TextTransform_.Parent_ = &ExpFrameTransform_;
	TextTransform_.Anchor_ = RectTransform::TopCenter;
}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::Update()
{
	//本体の大きさを計算
	ExpTransform_.Width_ = min((float)*NowExp_ / (float)*NextExp_,1.0f) * 750;

	//トランスフォームの更新
	ExpFrameTransform_.Update();
	ExpTransform_.Update();

	TextTransform_.Update();

}

/**
 * ポストエフェクトの後に呼ばれる描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::PostRender()
{
	//画像を描画
	ExpFrameImage_.Render();
	ExpImage_.Render();

	//レベルのフォントを作成
	char level[10];
	sprintf_s(level, "%d", Player_->GetParameter().Level_);

	//中心地を取得
	int y = Engine().GetScreenH();
	int x = Engine().GetScreenW();
	x /= 2;

	//レベルを描画
	Level_.Render(level);

}