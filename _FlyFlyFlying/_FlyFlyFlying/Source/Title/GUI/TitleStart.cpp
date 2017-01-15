/**
 * @file Source\Title\GUI\TitleStart.cpp
 *
 * タイトルスタートクラスの定義.
 */
#include"stdafx.h"
#include"TitleStart.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::Start()
{
	//画像読み込み
	StartImage_.Load("Image/Start.png");
	//トランスフォームの設定
	StartImage_.SetTransform(&StartRT_);

	//大きさ調整
	StartRT_.Width_ = 200;
	StartRT_.Height_ = 100;
	
	//位置調整
	StartRT_.Position_ = D3DXVECTOR2(0, -100);

	//アンカー設定
	StartRT_.Anchor_ = RectTransform::MiddleCenter;
}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::Update()
{
	StartRT_.Update();
}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::PostRender()
{
	StartImage_.Render();
}