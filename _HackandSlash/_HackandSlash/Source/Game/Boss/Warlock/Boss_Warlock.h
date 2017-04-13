/**
* ウォーロックのボスクラスの定義.
*/
#pragma once

#include"../IBoss.h"

#include"HFSM\IWarlockState.h"
class IWarlockState;

/**
* ウォーロックのボスクラス.
* 人間を裏切り悪魔と契約した魔法使い.
*/
class Boss_Warlock : public IBoss
{
public:

	/** アニメーションコード. */
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< 無効.
		Idol = 0,		//!< 待機.
		Walk,			//!< 歩行.
	};

	/** 状態コード. */
	enum class StateCodeE
	{
		Invalid = -1,	//!< 無効.
		Waiting = 0,	//!< 待機.
		Combat,			//!< 戦闘.
		Death,			//!< 死.
	};

public:

	/**
	* コンストラクタ.
	*/
	Boss_Warlock()
	{
	}

	/**
	* デストラクタ.
	*/
	~Boss_Warlock()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;

	/**
	* 更新.
	*/
	void Update()override;

	/**
	* 描画.
	*/
	void Render()override;

	/**
	* 解放.
	*/
	void Release()override;

	/**
	* アニメーションを変更.
	*
	* @param animcode	再生するアニメーションコード.
	* @param time		補間時間.
	*/
	void PlayAnimation(AnimationCodeE animcode, float time)
	{
		//現在再生しているアニメーションでなければ.
		if (Animation_.GetNowAnimationNo() != (int)animcode)
		{
			//変更.
			Animation_.PlayAnimation((int)animcode, time);
		}
	}

	/**
	* 状態遷移.
	*
	* @param nextstate	次の状態.
	*/
	void ChangeState(StateCodeE nextstate);

private:

	/**
	* ダメージ関数.
	*/
	void Damage()override;

	/**
	* アニメーション管理.
	*/
	void AnimationControl()override;

	/** 
	* HFSMの初期化.
	*/
	void InitHFSM();

private:

	/** 状態. */
	StateCodeE State_ = StateCodeE::Invalid;

	/** 状態リスト. */
	vector<unique_ptr<IWarlockState>> StateList_;

};