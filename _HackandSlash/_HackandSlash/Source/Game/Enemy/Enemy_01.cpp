/**
 * @file Source\Game\Monster\Enemy_01.cpp
 *
 * 物理攻撃をする敵クラスの実装.
 */
#include"stdafx.h"
#include"Enemy_01.h"

/*---------------------------------------------------------------------------------------------------------*/
#include"../GameCamera.h"

#include"../../Game/Item/ItemDataResource.h"
#include"../DropItem/DropItemManager.h"

//無名空間
namespace
{

	/** The animation event tbl[ monster 01 animation num]. */
	AnimationEventGroupS AnimationEventTbl[Enemy_01::AnimationCodeE::AnimationNum] =
	{
		//AnimationWaiting
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationWalk
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationRun
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_01
		{
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.1f, 0.1f, 1.0f, 5, "Joint_3_3", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.3f, 0.1f, 1.0f, 5, "Joint_3_3", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.5f, 0.1f, 1.0f, 5, "Joint_3_3", Vector3::Zero, 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationHit
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationDeath
		{
			END_ANIMATION_EVENT(),
		},
	};

	/** 消滅パーティクル. */
	ParticleParameterS DisappearanceParticle =
	{
		"Soul_01.png",						//!< テクスチャのファイルパス。
		Vector3(0.0f, 0.5f, 0.0f),		//!< 初速度。
		2.0f,								//!< 寿命。単位は秒。
		0.3f,								//!< 発生時間。単位は秒。
		0.4f,								//!< パーティクルの幅。
		0.4f,								//!< パーティクルの高さ。
		Vector3(0.3f, 0.0f, 0.3f),		//!< 初期位置のランダム幅。
		Vector3(0.0f, 0.3f, 0.0f),		//!< 初速度のランダム幅。
		Vector3(0.0f, 0.3f, 0.0f),		//!< 速度の積分のときのランダム幅。
		{									//!< UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。		
			Vector4(0.0f,  0.0f, 1.0f, 1.0f),
		},
		0,									//!< UVテーブルのサイズ。
		Vector3(0.0f, 0.0f, 0.0f),		//!< 重力。	
		true,								//!< 死ぬときにフェードアウトする？
		1.0f,								//!< フェードする時間。
		1.0f,								//!< 初期アルファ値。	
		true,								//!< ビルボード？
		1.0f,								//!< 輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		0,									//!< 0半透明合成、1加算合成。
	};
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Start()
{

	//スキンモデルデータをロード
	SMDResources().Load(SkinModelDataHandle_, "Enemy_01.X", &Animation_);
	//モデルレンダを初期化
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//基底クラスの初期化
	IEnemy::Start();

	//ステートを待機に設定
	ChangeState(StateCodeE::Waiting);

	//待機アニメーションを開始
	PlayAnimation(AnimationCodeE::Waiting,0.3f);

	//アニメーションのロープフラグを設定
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_01, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Hit, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Death, false);

	Radius_ = 0.3f;
	Height_ = 0.9f;
	//キャラクターコントローラの初期化
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	
	AnimationEvent_.Init(&ModelRender_, &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//コライダーの初期化
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	//コリジョンオブジェクトの初期化
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

	//Hpを設定.
	Hp_ = 30;

	//プレイヤーを攻撃し始める距離を設定.
	PlayerAttackDis_ = 1.0f;


}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Update()
{
	//ムーブスピードを取得
	Vector3 MoveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateCodeE::Waiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//プレイヤーを発見したので追いかけ状態に変化
			ChangeState(StateCodeE::Chase);
			break;
		}

		//スピードを緩める
		MoveSpeed.Scale(0.8f);

		//立ち止まり
		if (WaitingLT_ >= WaitingTime_)
		{
			//立ち止まりが終わったので徘徊開始
			ChangeState(StateCodeE::Loitering);

			//目的地を算出
			Destination_ = Vector3((Random().value() - 0.5f) * Distance_, 0, (Random().value() - 0.5f) * Distance_);
			Destination_.Add(DefaultPosition_);

			//立ち止まりローカルタイムを初期化
			WaitingLT_ = 0;
			break;
		}

		//立ち止まりローカルタイムに加算
		WaitingLT_ += Time().DeltaTime();
	}
	break;
	case StateCodeE::Loitering:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//プレイヤーを発見したので追いかけ状態に変化
			ChangeState(StateCodeE::Chase);
			break;
		}

		if (GetToDestinationDis() <= 0.2)
		{
			//目的地に到達したので待機状態に変化
			ChangeState(StateCodeE::Waiting);
			break;
		}

		//目的地までの方向ベクトルを取得
		Vector2 toD = GetToDestination();

		//ムーブスピードを設定
		MoveSpeed = Vector3(toD.x, 0, toD.y);

		//向いている方向に回転
		Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveSpeed.x, MoveSpeed.z)) + 180.0f);
	
	}
	break;
	case StateCodeE::Chase:
	{

		if (GetToPlayerDis() >= toPlayerMaxDis_ || Player_->GetDeathFlag())
		{
			//プレイヤーを見失ったので待機状態に変化
			ChangeState(StateCodeE::Waiting);
			break;
		}
		else if (GetToPlayerDis() <= PlayerAttackDis_ && !Player_->GetDeathFlag())
		{
			//プレイヤーを攻撃する距離まで追い詰めたので攻撃状態に変化
			ChangeState(StateCodeE::Attack);
			break;
		}

		//プレイヤーへの方向ベクトルを取得
		Vector2 toP = GetToPlayerDir();

		//ムーブスピードを設定
		MoveSpeed = Vector3(toP.x, 0, toP.y);

		//向いている方向に回転
		Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveSpeed.x, MoveSpeed.z)) + 180.0f);
	
	}
	break;
	case StateCodeE::Attack:
	{
		if (!Animation_.IsPlayAnim())
		{
			//攻撃のアニメーションが終わっていれば
			if (GetToPlayerDis() > PlayerAttackDis_ || Player_->GetDeathFlag())
			{
				//攻撃距離から離れたので追いかけ状態に変化
				ChangeState(StateCodeE::Chase);
				break;
			}
			else
			{
				//同じモーションをもう一度
				PlayAnimationAbs(AnimationCodeE::Attack_01, 0.3f);
			}
		}

		//移動情報を削除
		MoveSpeed = Vector3::Zero;
	
	}
	break;
	case StateCodeE::Hit:
	{
		if (!Animation_.IsPlayAnim())
		{
			//アニメーションが終わっているので追いかけ状態に変化
			ChangeState(StateCodeE::Chase);
			break;
		}
		
		//ダメージを受けているので動いていない
		MoveSpeed = Vector3::Zero;

	}
	break;
	case StateCodeE::Death:
	{
		if (!Animation_.IsPlayAnim())
		{

			if (isOnceDeath_)
			{
				isOnceDeath_ = false;

				//消滅パーティクルを発生.
				DisappearanceParticleSet("chestcontrol", DisappearanceParticle);

				//ドロップアイテムマネージャに登録
				g_DropItemManager->SetDropItem(Level_, Transform_.Position_);

			}

			//消滅時間のローカルタイムを加算
			DisappearanceLT_ += Time().DeltaTime();
			//消滅時間が経過した
			if (DisappearanceTime_ <= DisappearanceLT_)
			{
				//徐々に透明に
				Alpha_ = fmax(0.0f, Alpha_ - 0.01f);
				if (Alpha_ <= 0.0f)
				{
					// アニメーションが終了したのでノンアクティブに設定
					// することで削除される
					isActive_ = false;
					break;
				}
			}
		}
		//死んでいるので移動情報を削除
		MoveSpeed = Vector3::Zero;

	}
	break;
	
	default:
		break;
	}

	//キャラクターコントローラに移動情報を設定
	CharacterController_.SetMoveSpeed(MoveSpeed);
	//キャラクターコントローラの更新
	CharacterController_.Update();
	
	//計算終了したポジションを取得
	Transform_.Position_ = CharacterController_.GetPosition();

	//アニメーションイベントを更新
	AnimationEvent_.Update();

	//ダメージを更新
	Damage();

	//アニメーションを更新
	AnimationControl();

	//モデルレンダにアルファを設定
	ModelRender_.SetAlpha(Alpha_);

	//基底クラスを更新
	IEnemy::Update();

}

/**
 * アニメーション管理.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::AnimationControl()
{
	//アニメーションタイム
	float AnimationTime = Time().DeltaTime();
	
	//状態によってアニメーションを変化
	switch (State_)
	{
	case StateCodeE::Waiting:
		//待機アニメーション
		PlayAnimation(AnimationCodeE::Waiting, 0.3f);
		break;

	case StateCodeE::Loitering:
		//歩きアニメーション
		PlayAnimation(AnimationCodeE::Walk, 0.3f);
		break;

	case StateCodeE::Chase:
		//走りアニメーション
		PlayAnimation(AnimationCodeE::Run, 0.3f);
		break;

	case StateCodeE::Attack:
		//攻撃アニメーション
		PlayAnimation(AnimationCodeE::Attack_01, 0.3f);
		break;

	case StateCodeE::Hit:
		//ダメージアニメーション
		PlayAnimation(AnimationCodeE::Hit, 0.3f);
		break;

	case StateCodeE::Death:
		//死亡アニメーション
		PlayAnimation(AnimationCodeE::Death, 0.3f);
		break;

	default:
		break;
	}

	//アニメーションの更新
	Animation_.Update(AnimationTime);

}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Render()
{
	//基底クラスの描画
	IEnemy::Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Release()
{
}

/**
 * ダメージ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Damage()
{
	if (State_ == StateCodeE::Death)
	{
		//死んでる。
		return;
	}

	//位置計算
	float offset = Radius_ + Height_ * 0.5f;
	Vector3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;
	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));

	//位置情報を設定
	CollisionObject_->setWorldTransform(trans);

	//当たっているコリジョンを検出
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::AttributeE::DamageToEnemy,
		CollisionObject_.get()
	);

	if (!dmgCol)
	{
		//見つかっていない

		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		//位置情報を更新
		CollisionObject_->setWorldTransform(trans);
		
		//もう一度当たっているコリジョンを検出
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::AttributeE::DamageToEnemy,
			CollisionObject_.get()
		);
	}

	if (dmgCol != NULL && State_ != StateCodeE::Hit)
	{
		//ダメージコリジョンをみつけてダメージを受けている状態でない
		
		//ダメージを食らっている。
		Hp_ -= dmgCol->Damage_;

		if (Hp_ <= 0) 
		{
			//死亡。
	
			//死亡状態に変化
			ChangeState(StateCodeE::Death);

			//プレイヤーに経験値を加算
			Player_->AddExperience(2);

			//キャラクターコントローラの剛体を削除
			CharacterController_.RemoveRigidBody();

			
			isOnceDeath_ = true;

		}
		else 
		{
			//ヒット状態に変化
			ChangeState(StateCodeE::Hit);
		}

	}

}