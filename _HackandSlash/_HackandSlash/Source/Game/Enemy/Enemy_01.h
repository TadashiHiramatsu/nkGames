/**
 * @file Source\Game\Monster\Monster_01.h
 *
 * 物理攻撃をする敵クラスの定義.
 */
#pragma once

#include"IEnemy.h"

/**
 * 敵クラス.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class Enemy_01 : public IEnemy
{
public:

	/** アニメーションコード. */
	enum class AnimationCodeE
	{
		Invalid = -1,	//!< 無効
		Waiting = 0,	//!< 待機
		Walk,			//!< 歩き
		Run,			//!< 走り
		Attack_01,		//!< 攻撃１
		Hit,			//!< ダメージ
		Death,			//!< 死
		AnimationNum,	//!< アニメーションの数
	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	Enemy_01()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~Enemy_01()
	{
	}

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
	 * @param animCode		  再生するアニメーションコード.
	 * @param time 補間時間.
	 */
	void PlayAnimation(AnimationCodeE animCode, float time)
	{
		//現在のアニメーションではない
		if (Animation_.GetNowAnimationNo() != (int)animCode)
		{
			Animation_.PlayAnimation((int)animCode, time);
		}

	}
	/**
	 * 現在のアニメーションに関係なく設定する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param animCode	再生するアニメーションコード.
	 * @param time		補間時間.
	 */
	void PlayAnimationAbs(AnimationCodeE animCode, float time)
	{
		Animation_.PlayAnimation((int)animCode, time);
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



};