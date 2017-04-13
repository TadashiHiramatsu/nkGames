/**
* ウォーロックボスクラスのAIの
* 回転状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Turn.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Turn::Entry()
{
	IWarlockState::Entry();
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Turn::Update()
{
	IWarlockState::Update();
}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Turn::Exit()
{
	IWarlockState::Exit();
}
