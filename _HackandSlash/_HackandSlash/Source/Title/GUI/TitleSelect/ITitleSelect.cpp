/**
* タイトルシーンのセレクトの基底クラスの実装.
*/
#include"stdafx.h"
#include"ITitleSelect.h"

/**
* 初期化.
*/
void ITitleSelect::Start()
{
	//トランスフォームの設定.
	SelectImage_.SetTransform(&SelectRT_);

	SelectRT_.Height_ = 73 / 2;
}

/**
* 更新.
*/
void ITitleSelect::Update()
{
	//トランスフォームの更新.
	SelectRT_.Update();
}

/**
* ポストエフェクト後の描画.
*/
void ITitleSelect::PostRender()
{
	//画像の描画.
	SelectImage_.Render();
}
