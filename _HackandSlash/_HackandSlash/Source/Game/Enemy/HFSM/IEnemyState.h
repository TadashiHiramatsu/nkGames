/**
* 敵AIで使用するHFSMの基底クラスの定義.
*/
#pragma once

#include"../IEnemy.h"

/**
* 敵の状態の基底クラス.
*/
class IEnemyState : Noncopyable
{
public:

	/**
	* コンストラクタ.
	*
	* @param enemy	自身のポインタ.
	*/
	IEnemyState(IEnemy* enemy)
	{
		Enemy_ = enemy;
	}

	/**
	* デストラクタ.
	*/
	virtual ~IEnemyState()
	{
	}
	
	/**
	* 開始処理.
	* この状態に遷移した時に実行される.
	*/
	virtual void Entry()
	{
		LocalState_ = -1;
	}

	/**
	* 更新処理.
	* この状態の時に毎フレーム実行される.
	*/
	virtual void Update()
	{
	}

	/**
	* 終了処理.
	* この状態から遷移した時に実行される.
	*/
	virtual void Exit()
	{
	}

protected:

	/**
	* ローカルの状態を遷移する.
	*
	* @param nextstate	遷移後の状態.
	*/
	void ChangeLocalState(int nextstate)
	{
#ifdef _DEBUG
		if (nextstate < 0 && LocalStateList_.size() <= nextstate)
		{
			NK_ASSERT(false, "ローカルの状態に登録されていません");
			return;
		}
#endif // _DEBUG

		if (LocalState_ != -1)
		{
			//ローカルの状態が設定されていたら終了処理を行う.
			LocalStateList_[LocalState_]->Exit();
		}
		
		//次の状態に遷移.
		LocalState_ = nextstate;
		//開始処理を行う.
		LocalStateList_[LocalState_]->Entry();
	}

protected:

	/** ローカルの状態リスト. */
	vector<IEnemyState*> LocalStateList_;
	/** ローカルの状態. */
	int LocalState_ = -1;

	/** エネミークラスのポインタ. */
	IEnemy* Enemy_ = nullptr;

};