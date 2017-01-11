/**
 * @file Source\Game\Player\Player.h
 *
 * プレイヤークラスの定義.
 */
#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

/**
 * プレイヤークラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
class Player : public IGameObject
{
public:

	/**
	 * プレイヤーパラメータの構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	struct PlayerParameterS
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		PlayerParameterS()
		{
			Level_ = 1;
			Experience_ = 0;
			NextLevelExperience_ = 10;
			Attack_ = 1;
			MaxHp_ = NowHp_ = 100;
			InvincibleTime_ = 1.0f;
		}

	public:

		/** レベル. */
		int Level_;
		/** 現在の経験値. */
		int Experience_;
		/** 次のレベルへの経験値. */
		int NextLevelExperience_;
		/** 攻撃力. */
		int	Attack_;
		/** 体力. */
		int MaxHp_;
		/** 体力. */
		int NowHp_;
		/** 無敵時間. */
		int InvincibleTime_;

	};

	/** アニメーションコードの列挙. */
	enum AnimationCodeE
	{
		AnimationInvalid = -1,	//!< 無し
		AnimationWaiting = 0,	//!< 待機
		AnimationWalk,			//!< 歩き
		AnimationRun,			//!< 走り
		AnimationAttack,		//!< 攻撃
		AnimationHit,			//!< やられ
		AnimationDead,			//!< 死亡
		AnimationNum,			//!< アニメーションの数
	};


	/** ステートコードの列挙. */
	enum StateCodeE
	{
		StateWaiting = 0,	//!< 待機
		StateWalk,			//!< 歩き
		StateRun,			//!< 走り
		StateAttack,		//!< 攻撃
		StateDamage,		//!< やられ
		StateDead,			//!< 死亡
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Player();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	~Player();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Release()override;

	/**
	 * 攻撃を受けた.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void Damage();

	/**
	 * レベルアップ処理.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void ParameterUpdate();

	/**
	 * 経験値加算.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param add The add.
	 */
	void AddExperience(int add)
	{
		Parameter_.Experience_ += add;
	}

	/**
	 * プレイヤーパラメータの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The player parameter.
	 */
	PlayerParameterS& GetParameter()
	{
		return Parameter_;
	}

	/**
	 * ポジションの取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return The position.
	 */
	D3DXVECTOR3& GetPosition()
	{
		return Transform_.Position_;
	}

private:

	/**
	 * ステート更新関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param nextState State of the next.
	 */
	void ChangeState(StateCodeE nextState);

	/**
	 * アニメーション管理関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void AnimationControl();

	/**
	 * アニメーション切り替え関数.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimation(AnimationCodeE animCode, float interpolateTime);

private:

	/** ライト. */
	Light Light_;
	/** モデルレンダー. */
	ModelRender ModelRender_;
	/** アニメーション. */
	Animation Animation_;

	/** 状態. */
	StateCodeE State_;

	/** The radius. */
	float Radius_ = 0.0f;
	/** The height. */
	float Height_ = 0.0f;
	/** キャラクターコントローラ. */
	CharacterController CharacterController_;

	/** アニメーションイベント. */
	AnimationEventController AnimationEvent_;

	/** プレイヤーのパラメータ. */
	PlayerParameterS Parameter_;

	//ParticleEmitter Particle;
	//D3DXMATRIX* mParticle;
	//D3DXVECTOR3 ParticlePos;

	/** 左手武器のトランスフォーム. */
	Transform WeaponTransformL_;
	/** 左手武器のライト. */
	Light WeaponLightL_;
	/** 左手武器のモデルレンダー. */
	ModelRender WeaponModelRenderL_;

	/** 右手武器のトランスフォーム. */
	Transform WeaponTransformR_;
	/** 右手武器のライト. */
	Light WeaponLightR_;
	/** 右手武器のモデルレンダー. */
	ModelRender WeaponModelRenderR_;

	/** 無敵時間計測用ローカルタイム. */
	float InvincibleLT_ = 0.0f;
	/** ライフ回復時間用ローカルタイム. */
	float RecoveryLT_ = 0.0f;

	/** コリジョンオブジェクト. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** 球体形状コライダー. */
	unique_ptr<SphereCollider>	SphereShape_;

};