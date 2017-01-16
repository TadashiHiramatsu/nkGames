/**
 * @file Source\Game\Monster\Monster_01.h
 *
 * 物理攻撃をするモンスタークラスの定義.
 */
#pragma once

#include"IMonster.h"

/**
 * モンスタークラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class Monster_01 : public IMonster
{
public:

	/** アニメーションコード. */
	enum AnimationCode
	{
		AnimationInvalid = -1,	//!< 無効
		AnimationWaiting = 0,	//!< 待機
		AnimationWalk,			//!< 歩き
		AnimationRun,			//!< 走り
		AnimationAttack_01,		//!< 攻撃１
		AnimationAttack_02,		//!< 攻撃２
		AnimationHit,			//!< ダメージ
		AnimationDeath,			//!< 死
		AnimationNum,			//!< アニメーションの数
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	Monster_01();

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~Monster_01();

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Render()override;

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Release()override;

	/**
	 * ダメージ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Damage()override;

	/**
	 * アニメーションを変更する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimation(AnimationCode animCode, float interpolateTime)
	{
		//現在のアニメーションではない
		if (Animation_.GetNowAnimationNo() != animCode)
		{
			Animation_.PlayAnimation(animCode, interpolateTime);
		}

	}
	/**
	 * 現在のアニメーションに関係なく設定する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode		  The animation code.
	 * @param interpolateTime The interpolate time.
	 */
	void PlayAnimationAbs(AnimationCode animCode, float interpolateTime)
	{
		Animation_.PlayAnimation(animCode, interpolateTime);
	}

	/**
	 * アニメーション管理.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void AnimationControl()override;

private:

	/** コリジョンオブジェクト. */
	unique_ptr<btCollisionObject> CollisionObject_;
	/** 球体形状. */
	unique_ptr<SphereCollider> SphereShape_;

	/** 消滅までの時間(秒). */
	float DisappearanceTime_ = 5.0f;
	/** 消滅時間のローカルタイム. */
	float DisappearanceLT_ = 0.0f;

	/** 消滅パーティクル. */
	ParticleEmitter Particle_;
	/** 消滅パーティクルポジション. */
	D3DXVECTOR3 ParticlePos_;

};