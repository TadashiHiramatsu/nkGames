/**
* ウォーロックボスクラスのAIの
* 待機状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Waiting.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Waiting::Entry()
{
	IWarlockState::Entry();

	//移動速度を消す.
	Boss_->SetMoveSpeed(0.0f);
	Boss_->PlayAnimation(Boss_Warlock::AnimationCodeE::Idol,0.3f);
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Waiting::Update()
{
	IWarlockState::Update();

	Vector3 playerPos = Boss_->GetPlayerPosition();

	Vector3 toPlayer;
	toPlayer.Sub(playerPos, Boss_->Transform_.Position_);

	//プレイヤーとの距離.
	float toPlayerLen = toPlayer.Length();

	if (toPlayerLen < PlayerDiscovery_)
	{
		Boss_->ChangeState(Boss_Warlock::StateCodeE::Combat);
	}

}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Waiting::Exit()
{
	IWarlockState::Exit();
}
