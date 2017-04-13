/**
* ウォーロックボスクラスのAIの
* ダメージ状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Damage.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Damage::Entry()
{
	IWarlockState::Entry();
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Damage::Update()
{
	IWarlockState::Update();
}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Damage::Exit()
{
	IWarlockState::Exit();
}
