/**
* ウォーロックボスクラスのAIの
* 回転状態クラスの定義.
*/
#pragma once

#include"IWarlockState.h"

/**
* ウォーロックボスクラスのAIの
* 回転状態クラス
*/
class WarlockState_Turn : public IWarlockState
{
public:

	/**
	* コンストラクタ.
	*/
	WarlockState_Turn(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* デストラクタ.
	*/
	~WarlockState_Turn()
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