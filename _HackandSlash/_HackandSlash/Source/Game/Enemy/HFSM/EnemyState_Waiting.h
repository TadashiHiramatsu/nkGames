/**
* 敵の待機状態クラスの定義.
*/
#pragma once

#include"IEnemyState.h"

/**
* 敵の待機状態クラス.
*/
class EnemyState_Waiting : public IEnemyState
{
private:

	/** ローカルの状態コード. */
	enum class LocalStateCodeE
	{
		Stand,	//!< 立ち状態.
	};

public:

	/**
	* コンストラクタ.
	*
	* @param enemy	自分のポインタ.
	*/
	EnemyState_Waiting(IEnemy* enemy);
	

	/**
	* デストラクタ.
	*/
	~EnemyState_Waiting()
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

	/** 目的地. */
	Vector3 Destination_ = Vector3::Zero;

};