/**
* ボス_01クラスの実装.
*/
#include"stdafx.h"
#include"Boss_01.h"

/**
* 初期化.
*/
void Boss_01::Start()
{
	//モデルデータをリソース登録して読み込み.
	SMDResources().Load(SkinModelDataHandle_, "Boss_01.X", &Animation_);

	//モデルレンダーを初期化.
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//基底クラスの初期化.
	IBoss::Start();

	//待機状態に変化.
	ChangeState(StateCodeE::Waiting);

	//待機アニメーションを開始
	PlayAnimation(AnimationCodeE::Waiting, 0.3f);

	Transform_.Position_ = Vector3(10, 5, 0);

	Radius_ = 1.2f;
	Height_ = 2.5f;
	//キャラクターコントローラの初期化
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

}

/**
* 更新.
*/
void Boss_01::Update()
{
	//移動ベクトル.
	Vector3 movespeed = CharacterController_.GetMoveSpeed();
	
	switch (State_)
	{
	case StateCodeE::Spawn:
		break;
	case StateCodeE::Waiting:
		break;
	case StateCodeE::Chase:
		break;
	case StateCodeE::Turn:
		break;
	case StateCodeE::Attack:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}

	//キャラクターコントローラに移動情報を設定
	CharacterController_.SetMoveSpeed(movespeed);
	//キャラクターコントローラの更新
	CharacterController_.Update();

	//計算終了したポジションを取得
	Transform_.Position_ = CharacterController_.GetPosition();

	//アニメーションを更新
	AnimationControl();

	//基底クラスを更新
	IBoss::Update();
}

/**
* 描画.
*/
void Boss_01::Render()
{
	//基底クラスの描画
	IBoss::Render();
}

/**
* 解放.
*/
void Boss_01::Release()
{
	//剛体の削除.
	CharacterController_.RemoveRigidBody();
}

/**
* ダメージ関数.
*/
void Boss_01::Damage()
{
}

/**
* アニメーション管理.
*/
void Boss_01::AnimationControl()
{
	//アニメーションタイム
	float time = Time().DeltaTime();

	switch (State_)
	{
	case StateCodeE::Spawn:
		break;
	case StateCodeE::Waiting:
		//待機アニメーション.
		PlayAnimation(AnimationCodeE::Waiting, 0.3f);
		break;
	case StateCodeE::Chase:
		break;
	case StateCodeE::Turn:
		break;
	case StateCodeE::Attack:
		break;
	case StateCodeE::Death:
		break;
	default:
		break;
	}
	
	//アニメーション更新.
	Animation_.Update(time);

}
