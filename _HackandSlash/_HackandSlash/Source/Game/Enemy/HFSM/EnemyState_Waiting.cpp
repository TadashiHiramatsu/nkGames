/**
* 敵の待機状態クラスの実装.
*/
#include"stdafx.h"
#include"EnemyState_Waiting.h"

#include"EnemyState_Stand.h"
#include"EnemyState_Loitering.h"

/**
* コンストラクタ.
*
* @param enemy	自分のポインタ.
*/
EnemyState_Waiting::EnemyState_Waiting(IEnemy * enemy) :
	IEnemyState(enemy)
{
	LocalStateList_.push_back(new EnemyState_Stand(enemy));
	//LocalStateList_.push_back(new EnemyState_Loitering(enemy));
}

/**
* 開始処理.
* この状態に遷移した時に実行される.
*/
void EnemyState_Waiting::Entry()
{
	IEnemyState::Entry();
	ChangeLocalState((int)LocalStateCodeE::Stand);
}

/**
* 更新処理.
* この状態の時に毎フレーム実行される.
*/
void EnemyState_Waiting::Update()
{
	LocalStateList_[LocalState_]->Update();
}

/**
* 終了処理.
* この状態から遷移した時に実行される.
*/
void EnemyState_Waiting::Exit()
{
	IEnemyState::Exit();
}
