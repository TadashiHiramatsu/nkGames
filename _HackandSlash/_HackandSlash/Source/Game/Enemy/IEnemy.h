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
	enum StateCodeE
	{
		StateSpawn,		//!< 出現
		StateWaiting,	//!< 立ち止まり
		StateLoitering, //!< 徘徊
		StateChase,		//!< 追いかけ
		StateAttack,	//!< 攻撃
		StateDamage,	//!< ダメージ
		StateDeath,		//!< そして死
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
	 * ダメージを受けた.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	virtual void Damage(){}

	/**
	 * ポジションを設定.
	 * 出現位置を設定するときのために使っているので他で使うと不具合.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] pos The position.
	 */
	void SetPosition(D3DXVECTOR3& pos)
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
	D3DXVECTOR2& GetToPlayerDir()
	{
		D3DXVECTOR2 toP = D3DXVECTOR2(Player_->Transform_.Position_.x, Player_->Transform_.Position_.z) - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		D3DXVec2Normalize(&toP, &toP);
		return toP;
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
		D3DXVECTOR3 toP = Player_->Transform_.Position_ - Transform_.Position_;
		return D3DXVec2Length(&D3DXVECTOR2(toP.x, toP.z));
	}

	/**
	 * 目的地までの方向ベクトルを取得.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @return to destination.
	 */
	D3DXVECTOR2& GetToDestination()
	{
		D3DXVECTOR2 toD = Destination_ - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		D3DXVec2Normalize(&toD, &toD);
		return toD;
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
		D3DXVECTOR2 toD = Destination_ - D3DXVECTOR2(Transform_.Position_.x, Transform_.Position_.z);
		return D3DXVec2Length(&toD);
	}

protected:

	/** スキンモデルデータハンドル. */
	SkinModelDataHandle SkinModelDataHandle_;
	/** モデルレンダ. */
	ModelRender ModelRender_;
	/** アニメーション. */
	Animation Animation_;

	/** The radius. */
	float Radius_;
	/** The height. */
	float Height_;
	/** キャラクターコントローラ. */
	CharacterController CharacterController_;

	/** ヒットポイント. */
	int Hp_;

	/** スポーン位置 ここからの距離移動できる. */
	D3DXVECTOR3 DefaultPosition_;
	/** 距離. */
	float Distance_;
	/** 目的地. */
	D3DXVECTOR2 Destination_;

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

	/** アルファデータ. */
	float Alpha_ = 1.0f;

	//死亡パーティクルを出すための一度きりのフラグ
	bool isOnceDeath = false;

};