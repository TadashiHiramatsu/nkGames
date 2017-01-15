/**
 * @file Source\Title\GUI\TitleContinue.cpp
 *
 * タイトルコンティニュークラスの実装.
 */
#include"stdafx.h"
#include"TitleContinue.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::Start()
{
	ContinueImage_.Load("Image/Continue.png");
	ContinueImage_.SetTransform(&ContinueRT_);

	ContinueRT_.Width_ = 180;
	ContinueRT_.Height_ = 80;

	ContinueRT_.Position_ = D3DXVECTOR2(0, -200);

	ContinueRT_.Anchor_ = RectTransform::MiddleCenter;

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::Update()
{
	ContinueRT_.Update();
}

/**
 * ポストエフェクト後の描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::PostRender()
{
	ContinueImage_.Render();
}
