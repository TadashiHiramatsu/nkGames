/**
* ウォーロックボスクラスのAIの
* 戦闘状態クラスの定義.
*/
#pragma once

#include"IWarlockState.h"

class WarlockState_Combat : public IWarlockState
{
private:

	/** ローカルの状態コード. */
	enum class LocalStateCodeE
	{
		Invalid = -1,	//!< 無効.
		Stand,			//!< 立ち.
		Chase,			//!< 追従.
		Turn,			//!< 回転.
		Attack,			//!< 攻撃.
		Damage,			//!< ダメージ.
	};

public:

	/**
	* コンストラクタ.
	*/
	WarlockState_Combat(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
		InitLocalState();
	}

	/**
	* デストラクタ.
	*/
	~WarlockState_Combat()
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

	/**
	* ローカルの状態を初期化.
	*/
	void InitLocalState();

private:

	Vector3 MoveDirection_ = Vector3::Zero;

};