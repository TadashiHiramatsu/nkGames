/**
* タイトルセレクトのニューゲームクラスの実装.
*/
#include"stdafx.h"
#include"TitleSelect_NewGame.h"

#include"..\..\..\Game\GameScene.h"

/**
* 初期化.
*/
void TitleSelect_NewGame::Start()
{
	//ニューゲーム画像の初期化
	SelectImage_.Load("Image/new_game.png");
	ITitleSelect::Start();

	//位置設定.
	SelectRT_.Position_ = Vector3(300, -100, 0);

	//大きさを設定.
	SelectRT_.Width_ = 464 / 2;
}

/**
* 更新.
*/
void TitleSelect_NewGame::Update()
{
	ITitleSelect::Update();
}

/**
* ポストエフェクト後の描画.
*/
void TitleSelect_NewGame::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* 選択された時.
*/
bool TitleSelect_NewGame::OnTrigger()
{
	//ゲームシーンに移行.
	SceneManager().ChangeScene<GameScene>();

	return true;
}
