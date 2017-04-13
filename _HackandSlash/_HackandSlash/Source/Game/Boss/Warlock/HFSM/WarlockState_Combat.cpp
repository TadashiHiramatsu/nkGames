/**
* ウォーロックボスクラスのAIの
* 戦闘状態クラスの実装.
*/
#include"stdafx.h"
#include"WarlockState_Combat.h"

#include"WarlockState_Stand.h"
#include"WarlockState_Chase.h"
#include"WarlockState_Turn.h"
#include"WarlockState_Attack.h"
#include"WarlockState_Damage.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void WarlockState_Combat::Entry()
{
	IWarlockState::Entry();

	ChangeLocalState((int)LocalStateCodeE::Stand);
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void WarlockState_Combat::Update()
{
	IWarlockState::Update();

	LocalStateList_[LocalState_]->Update();

	//目的地までの方向ベクトルを取得
	Vector3 playerPos = Boss_->GetPlayerPosition();

	Vector3 toPlayer;
	toPlayer.Sub(playerPos, Boss_->Transform_.Position_);

	//移動方向を設定
	MoveDirection_ = Vector3(toPlayer.x, 0, toPlayer.z);

	//向いている方向に回転
	Boss_->Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveDirection_.x, MoveDirection_.z)) + 180.0f);

}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void WarlockState_Combat::Exit()
{
	IWarlockState::Exit();
}

/**
* ローカルの状態を初期化.
*/
void WarlockState_Combat::InitLocalState()
{
	//立ち状態.
	LocalStateList_.push_back(unique_ptr<WarlockState_Stand>(new WarlockState_Stand(Boss_)));
	//追従状態.
	LocalStateList_.push_back(unique_ptr<WarlockState_Chase>(new WarlockState_Chase(Boss_)));
	//回転状態.
	LocalStateList_.push_back(unique_ptr<WarlockState_Turn>(new WarlockState_Turn(Boss_)));
	//攻撃状態.
	LocalStateList_.push_back(unique_ptr<WarlockState_Attack>(new WarlockState_Attack(Boss_)));
	//ダメージ状態.
	LocalStateList_.push_back(unique_ptr<WarlockState_Damage>(new WarlockState_Damage(Boss_)));

	
}
