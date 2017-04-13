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

	/**
	* プレイヤーのポインタを取得.
	*/
	const Player* GetPlayer() const
	{
		return Player_;
	}

	/**
	* プレイヤーの座標を取得.
	*/
	const Vector3& GetPlayerPosition() const
	{
		return Player_->Transform_.Position_;
	}

	/**
	* 移動速度を設定.
	*
	* @param speed	移動速度(秒).
	*/
	void SetMoveSpeed(float speed)
	{
		MoveSpeed_ = speed;
	}

	/**
	* 移動速度を取得.
	*
	* @return 移動速度(秒).
	*/
	float GetMoveSpeed()
	{
		return MoveSpeed_;
	}

protected:

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

	/** プレイヤーのポインタ. */
	const Player* Player_ = nullptr;

	/** 移動速度. */
	float MoveSpeed_ = 80.0f;
	/** 移動方向. */
	Vector3 MoveDir_ = Vector3::Zero;


};