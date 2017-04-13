/**
* ウォーロックボスクラスのAIの
* 死亡状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Death.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Death::Entry()
{
	IWarlockState::Entry();

}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Death::Update()
{
	IWarlockState::Update();

}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Death::Exit()
{
	IWarlockState::Exit();

}
