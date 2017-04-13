/**
* ウォーロックボスクラスのAIの
* 死亡状態クラスの定義.
*/
#pragma once

#include"IWarlockState.h"

class WarlockState_Death : public IWarlockState
{
public:

	/**
	* コンストラクタ.
	*/
	WarlockState_Death(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* デストラクタ.
	*/
	~WarlockState_Death()
	{
	}

	/**
	* 開始処理.
	* この状態に遷移した時に実行される.
	*/
	void Entry();

	/**
	* 更新処理.
	* この状態の時に毎フレーム実行される.
	*/
	void Update();

	/**
	* 終了処理.
	* この状態から遷移した時に実行される.
	*/
	void Exit();

private:

};