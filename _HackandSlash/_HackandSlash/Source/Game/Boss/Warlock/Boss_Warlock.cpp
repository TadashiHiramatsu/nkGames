/**
* ウォーロックのボスクラスの実装.
*/
#include"stdafx.h"
#include"Boss_Warlock.h"

#include"HFSM\WarlockState_Waiting.h"
#include"HFSM\WarlockState_Combat.h"
#include"HFSM\WarlockState_Death.h"

/**
* 初期化.
*/
void Boss_Warlock::Start()
{
	//モデルデータをリソース登録して読み込み.
	SMDResources().Load(SkinModelDataHandle_, "Boss_Warlock.X", &Animation_);

	//モデルレンダーを初期化.
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//基底クラスの初期化.
	IBoss::Start();

	//待機アニメーションを開始
	PlayAnimation(AnimationCodeE::Idol, 0.3f);

	Transform_.Position_ = Vector3(10, 5, 0);

	Radius_ = 1.8f;
	Height_ = 2.5f;
	//キャラクターコントローラの初期化
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

	InitHFSM();
}

/**
* 更新.
*/
void Boss_Warlock::Update()
{
	//移動ベクトル.
	Vector3 movedir = CharacterController_.GetMoveSpeed();
	
	StateList_[(int)State_]->Update();

	switch (State_)
	{
	case StateCodeE::Waiting:
		break;
	case StateCodeE::Combat:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}

	//キャラクターコントローラに移動情報を設定
	Vector3 move = movedir;
	move.Normalize();
	move.Scale(MoveSpeed_);
	CharacterController_.SetMoveSpeed(move);
	//キャラクターコントローラの更新
	CharacterController_.Update();

	//計算終了したポジションを取得
	Transform_.Position_ = CharacterController_.GetPosition();

	//アニメーションを更新
	AnimationControl();

	//基底クラスの更新
	IBoss::Update();
}

/**
* 描画.
*/
void Boss_Warlock::Render()
{
	//基底クラスの描画
	IBoss::Render();
}

/**
* 解放.
*/
void Boss_Warlock::Release()
{
	//剛体の削除.
	CharacterController_.RemoveRigidBody();
}

/**
* ダメージ関数.
*/
void Boss_Warlock::Damage()
{
}

/**
* アニメーション管理.
*/
void Boss_Warlock::AnimationControl()
{
	//アニメーションタイム
	float time = Time().DeltaTime();

	//アニメーション更新.
	Animation_.Update(time);
}

/**
* 状態遷移.
*
* @param nextstate	次の状態.
*/
void Boss_Warlock::ChangeState(StateCodeE nextstate)
{
	if (State_ != StateCodeE::Invalid)
	{
		//状態が設定されている.
		StateList_[(int)State_]->Exit();
	}

	State_ = nextstate;

	//開始処理を実行.
	StateList_[(int)State_]->Entry();

}

/**
* HFSMの初期化.
*/
void Boss_Warlock::InitHFSM()
{
	//待機状態
	StateList_.push_back(unique_ptr<WarlockState_Waiting>(new WarlockState_Waiting(this)));
	//戦闘状態
	StateList_.push_back(unique_ptr<WarlockState_Combat>(new WarlockState_Combat(this)));
	//死亡状態
	StateList_.push_back(unique_ptr<WarlockState_Death>(new WarlockState_Death(this)));

	//待機状態に変化.
	ChangeState(StateCodeE::Waiting);
}
