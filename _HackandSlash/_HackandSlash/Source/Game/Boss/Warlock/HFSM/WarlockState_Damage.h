/**
* ウォーロックボスクラスのAIの
* ダメージ状態クラスの定義.
*/
#pragma once

#include"IWarlockState.h"

/**
* ウォーロックボスクラスのAIの
* ダメージ状態クラス
*/
class WarlockState_Damage : public IWarlockState
{
public:

	/**
	* コンストラクタ.
	*/
	WarlockState_Damage(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* デストラクタ.
	*/
	~WarlockState_Damage()
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