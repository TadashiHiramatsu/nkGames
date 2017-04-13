/**
* ウォーロックボスクラスのAIの
* 立ち状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Stand.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Stand::Entry()
{
	IWarlockState::Entry();

	//徐々に緩める.
	float movespeed = Boss_->GetMoveSpeed();
	Boss_->SetMoveSpeed(movespeed * 0.8f);

	//アニメーションを変更.
	Boss_->PlayAnimation(Boss_Warlock::AnimationCodeE::Walk,0.3f);
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Stand::Update()
{
	IWarlockState::Update();
	
	//徐々に緩める.
	float movespeed = Boss_->GetMoveSpeed();
	Boss_->SetMoveSpeed(movespeed * 0.8f);
}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Stand::Exit()
{
	IWarlockState::Exit();
}
