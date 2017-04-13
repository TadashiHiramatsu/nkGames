/**
* タイトルセレクトのコンティニュークラスの定義.
*/
#include"stdafx.h"
#include"TitleSelect_Continue.h"

#include"..\..\..\Game\GameScene.h"

/**
* 初期化.
*/
void TitleSelect_Continue::Start()
{
	//ニューゲーム画像の初期化
	SelectImage_.Load("Image/continue.png");
	ITitleSelect::Start();

	//位置設定.
	SelectRT_.Position_ = Vector3(300, -150, 0);

	//大きさを設定.
	SelectRT_.Width_ = 374 /2;
}

/**
* 更新.
*/
void TitleSelect_Continue::Update()
{
	ITitleSelect::Update();
}

/**
* ポストエフェクト後の描画.
*/
void TitleSelect_Continue::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* 選択された時.
*/
bool TitleSelect_Continue::OnTrigger()
{
	return false;

	//ゲームシーンに移行.
	SceneManager().ChangeScene<GameScene>();

	return true;
}
