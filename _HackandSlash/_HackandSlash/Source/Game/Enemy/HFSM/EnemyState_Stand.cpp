/**
* 敵の立ち状態クラスの実装.
*/
#include"stdafx.h"
#include"EnemyState_Stand.h"

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void EnemyState_Stand::Entry()
{

}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void EnemyState_Stand::Update()
{
	//移動速度.
	float speed = Enemy_->GetMoveSpeed();

	//徐々に止まる.
	speed *= 0.8f;

	//移動速度を設定.
	Enemy_->SetMoveSpeed(speed);
}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void EnemyState_Stand::Exit()
{

}
