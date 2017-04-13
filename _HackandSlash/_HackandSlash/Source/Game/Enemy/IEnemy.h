/**
 * @file Source\Game\Monster\IEnemy.h
 *
 * 敵の基底クラスの定義.
 */
#pragma once

#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\Player\Player.h"
#include"../GameCamera.h"

/**
 * 敵の基底クラス.
 * すべての敵はこのクラスを継承する
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class IEnemy : public IGameObject
{
protected:

	/** ステートコード. */
	enum class StateCodeE
	{
		Spawn,		//!< 出現.
		Waiting,	//!< 立ち止まり.
		Loitering,	//!< 徘徊.
		Chase,		//!< 追いかけ.
		Attack,		//!< 攻撃.
		Hit,		//!< ヒット.
		Death,		//!< 死.
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	IEnemy();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual ~IEnemy();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Release()override;

	/**
	 * ダメージ関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Damage()
	{
	}

	/**
	 * ポジションを設定.
	 * 出現位置を設定するときのために使っているので他で使うと不具合.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] pos The position.
	 */
	void SetPosition(Vector3& pos)
	{
		Transform_.Position_ = pos;
		DefaultPosition_ = pos;
	}

	/**
	* プレイヤーのポインタを設定.
	*
	* @author HiramatsuTadashi
	* @date 2017/01/11
	*
	* @param [in,out] p If non-null, the Player to process.
	*/
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

	/**
	* レベルを設定.
	*/
	void SetLevel(int l)
	{
		Level_ = l;
	}

	/**
	* 移動速度を設定.
	*
	* @param speed	移動速度.
	*/
	void SetMoveSpeed(float speed)
	{
		MoveSpeed_ = speed;
	}

	/**
	* 移動速度を取得.
	*/
	float GetMoveSpeed() const
	{
		return MoveSpeed_;
	}

	/**
	* 移動方向を設定.
	*
	* @param dir	移動方向ベクトル.
	*/
	void SetMoveDirection(const Vector3& dir)
	{
		MoveDirection_ = dir;
	}

	/**
	* 移動方向を取得.
	*/
	const Vector3& GetMoveDirection() const
	{
		return MoveDirection_;
	}

protected:

	/**
	 * Stateを変更する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param nextState 変更後のStateCode.
	 */
	void ChangeState(StateCodeE nextState)
	{
		State_ = nextState;
	}

	/**
	 * アニメーション管理.
	 * 継承先のクラスで実装する
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void AnimationControl() 
	{
	}

	/**
	 * プレイヤーへの方向ベクトルを計算.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to player dir.
	 */
	Vector2& GetToPlayerDir()
	{
		Vector3 toP;
		toP.Sub(Player_->Transform_.Position_, Transform_.Position_);
		toP.y = 0;
		toP.Normalize();
		return Vector2(toP.x, toP.z);
	}

	/**
	 * プレイヤーとの距離を計算. 
	 * 高さを考慮しない距離を返します.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to player dis.
	 */
	float GetToPlayerDis()
	{
		Vector3 toP;
		toP.Sub(Player_->Transform_.Position_ ,Transform_.Position_);
		toP.y = 0;
		return toP.Length();
	}

	/**
	 * 目的地までの方向ベクトルを取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination.
	 */
	Vector2& GetToDestination()
	{
		Vector3 toD;
		toD.Sub(Destination_, Transform_.Position_);
		toD.y = 0;
		toD.Normalize();
		return Vector2(toD.x, toD.z);
	}

	/**
	 * 目的地までの距離を計算. 
	 * 高さを考慮しない距離を返します.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination dis.
	 */
	float GetToDestinationDis()
	{
		Vector3 toD;
		toD.Sub(Destination_, Transform_.Position_);
		toD.y = 0;
		return toD.Length();
	}

	/**
	* 消滅パーティクルの発生. 
	*
	* @param bonename	ボーン名.
	* @param param		パーティクル情報.
	*/
	void DisappearanceParticleSet(char* bonename, const ParticleParameterS& param)
	{
		//行列を取得.
		Matrix posmatrix = *ModelRender_.FindBoneWorldMatrix(bonename);
		
		//座標を取得.
		Vector3 pos;
		pos.x = posmatrix.m[3][0];
		pos.y = posmatrix.m[3][1];
		pos.z = posmatrix.m[3][2];

		//寿命時間(秒).
		float LifeTime = 8.0f;

		//パーティクルエミッタを作成.
		ParticleEmitter* pe = NewGO<ParticleEmitter>();
		//初期化.
		pe->Start(g_MainCamera->GetCamera(), param, pos, LifeTime);
	}

protected:

	/** スキンモデルデータハンドル. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** モデルレンダ. */
	ModelRender ModelRender_;
	/** アニメーション. */
	Animation Animation_;

	/** 半径. */
	float Radius_;
	/** 高さ. */
	float Height_;
	/** キャラクターコントローラ. */
	CharacterController CharacterController_;

	/** ヒットポイント. */
	int Hp_;

	/** スポーン位置 ここからの距離移動できる. */
	Vector3 DefaultPosition_ = Vector3::Zero;
	/** 距離. */
	float Distance_;
	/** 目的地. */
	Vector3 Destination_ = Vector3::Zero;

	/** プレイヤーのポインタ. */
	Player* Player_;
	/**   
	 * プレイヤーを追いかける最大距離   
	 * 見つける距離も兼用. 
	 */
	float toPlayerMaxDis_; 
	/** プレイヤーを攻撃し始める距離. */
	float PlayerAttackDis_;

	/** 立ち止まる時間. */
	float WaitingTime_;
	/** 立ち止まる時間計測のためのローカルタイム. */
	float WaitingLT_;

	/** ステート. */
	StateCodeE State_;

	/** アニメーションイベント. */
	AnimationEventController AnimationEvent_;

	/** アルファ値. */
	float Alpha_ = 1.0f;

	/** 死亡した判定の一度きりのフラグ. */
	bool isOnceDeath_ = false;

	/** 消滅までの時間(秒). */
	float DisappearanceTime_ = 5.0f;
	/** 消滅時間のローカルタイム. */
	float DisappearanceLT_ = 0.0f;

	/** レベル. */
	int Level_ = 1;

	/** 移動速度. */
	float MoveSpeed_ = 50.0f;
	/** 移動方向. */
	Vector3 MoveDirection_ = Vector3::Zero;

};