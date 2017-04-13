/**
* タイトルセレクトのエグジットクラスの定義.
*/
#include"stdafx.h"
#include"TitleSelect_Exit.h"

/**
* 初期化.
*/
void TitleSelect_Exit::Start()
{
	//ニューゲーム画像の初期化
	SelectImage_.Load("Image/exit.png");
	ITitleSelect::Start();

	//位置設定.
	SelectRT_.Position_ = Vector3(300, -200, 0);

	//大きさを設定.
	SelectRT_.Width_ = 173 / 2;
}

/**
* 更新.
*/
void TitleSelect_Exit::Update()
{
	ITitleSelect::Update();
}

/**
* ポストエフェクト後の描画.
*/
void TitleSelect_Exit::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* 選択された時.
*/
bool TitleSelect_Exit::OnTrigger()
{
	Engine().GameExit();

	return true;
}
