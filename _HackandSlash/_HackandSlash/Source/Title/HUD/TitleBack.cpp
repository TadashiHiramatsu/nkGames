/**
 * @file Source\Title\HUD\TitleBack.cpp
 *
 * タイトルバッククラスの実装.
 */
#include"stdafx.h"
#include"TitleBack.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::Start()
{
	//画像読み込み
	BackImage_.Load("Image/TitleBack.jpg");
	//トランスフォーム設定
	BackImage_.SetTransform(&BackRT_);

	//大きさをスクリーンサイズに設定
	BackRT_.Width_ = Engine().GetScreenW();
	BackRT_.Height_ = Engine().GetScreenH();

	//アンカーを中心に設定
	BackRT_.Anchor_ = AnchorPresetE::MiddleCenter;

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::Update()
{
	//トランスフォームの更新
	BackRT_.Update();
}

/**
 * ポストエフェクト後の描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::PostRender()
{
	//背景画像の描画
	BackImage_.Render();
}