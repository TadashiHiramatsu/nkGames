/**
 * @file Source\Title\HUD\TitleBack.cpp
 *
 * タイトルバッククラスの実装.
 */
#include"stdafx.h"
#include"TitleBack.h"

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
TitleBack::TitleBack()
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
TitleBack::~TitleBack()
{
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::Start()
{
	BackImage_.Load("Image/TitleBack.jpg");
	BackImage_.SetTransform(&BackRT_);

	BackRT_.Width_ = Engine().GetScreenW();
	BackRT_.Height_ = Engine().GetScreenH();

	BackRT_.Anchor_ = RectTransform::MiddleCenter;
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