/**
* ボスの基底クラスの定義.
*/
#pragma once

#include"../Player/Player.h"

/**
* ボスの基底クラス.
* 全てのボスモンスターはこれを継承する.
*/
class IBoss : public IGameObject
{
protected:

	/** 状態コード. */
	enum class StateCodeE
	{
		Spawn,		//!< 出現.
		Waiting,	//!< 立ち止まり.
		Chase,		//!< 追いかけ.
		Turn,		//!< 曲がる.
		Attack,	//!< 攻撃.
		Death,		//!< 死.
	};

public:

	/**
	* コンストラクタ.
	*/
	IBoss()
	{
	}

	/**
	* デストラクタ.
	*/
	virtual ~IBoss()
	{
		Release();
	}

	/**
	* 初期化.
	*/
	virtual void Start()override;

	/**
	* 更新.
	*/
	virtual void Update()override;

	/**
	* 描画.
	*/
	virtual void Render()override;

	/**
	* 解放.
	*/
	virtual void Release()override;

	/**
	* ダメージ関数.
	*/
	virtual void Damage()
	{
	}

	/**
	* プレイヤーのポインタを設定.
	*/
	void SetPlayer(const Player* p)
	{
		Player_ = p;
	}

protected:

	/**
	* 状態遷移.
	*
	* @param nextstate	次の状態.
	*/
	void ChangeState(StateCodeE nextstate)
	{
		State_ = nextstate;
	}
	
	/**
	* アニメーション管理.
	* 継承先のクラスで実装する.
	*/
	virtual void AnimationControl()
	{
	}

protected:

	/** スキンモデルデータハンドル. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** モデルレンダー. */
	ModelRender ModelRender_;
	/** アニメーション. */
	Animation Animation_;

	/** 半径. */
	float Radius_ = 0.5f;
	/** 高さ. */
	float Height_ = 0.5f;
	/** キャラクターコントローラ. */
	CharacterController CharacterController_;

	/** 状態. */
	StateCodeE State_;

	/** プレイヤーのポインタ. */
	const Player* Player_ = nullptr;

};