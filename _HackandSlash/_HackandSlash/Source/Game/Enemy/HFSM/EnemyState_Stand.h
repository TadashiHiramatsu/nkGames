/**
* 敵の立ち状態クラスの定義.
*/
#pragma once

#include"IEnemyState.h"

/**
* 敵の立ち状態クラス.
*/
class EnemyState_Stand : public IEnemyState 
{
public:

	/**
	* コンストラクタ.
	*
	* @param enemy 自分のポインタ.
	*/
	EnemyState_Stand(IEnemy* enemy) :
		IEnemyState(enemy)
	{
	}

	/**
	* デストラクタ.
	*/
	~EnemyState_Stand()
	{
	}

	/**
	* 開始処理.
	* この状態に遷移した時に実行される.
	*/
	void Entry()override;

	/**
	* 更新処理.
	* この状態の時に毎フレーム実行される.
	*/
	void Update()override;

	/**
	* 終了処理.
	* この状態から遷移したときに実行される.
	*/
	void Exit()override;

private:

	/** 立ち止まる時間. */
	float StandTime_ = 1.0f;
	/** 立ち止まる時間計測のためのローカルタイム. */
	float StandLocalTime_ = 0.0f;

};