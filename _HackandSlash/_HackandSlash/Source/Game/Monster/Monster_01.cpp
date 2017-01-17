/**
 * @file Source\Game\Monster\Monster_01.cpp
 *
 * 物理攻撃をするモンスタークラスの実装.
 */
#include"stdafx.h"
#include"Monster_01.h"

/*---------------------------------------------------------------------------------------------------------*/
#include"../GameCamera.h"

#include"../Item/ItemResource.h"
#include"../GUI/DropItem.h"

//無名空間
namespace
{

	/** The animation event tbl[ monster 01 animation num]. */
	AnimationEventGroupS AnimationEventTbl[Monster_01::AnimationNum] = 
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
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.0f, 1.0f, 1.0f, 10, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.1f, 1.0f, 1.0f, 10, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.2f, 1.0f, 1.0f, 10, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.3f, 1.0f, 1.0f, 10, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.4f, 1.0f, 1.0f, 10, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_02
		{
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
		D3DXVECTOR3(0.0f, 0.3f, 0.0f),		//!< 初速度。
		1.0f,								//!< 寿命。単位は秒。
		0.001f,								//!< 発生時間。単位は秒。
		0.2f,								//!< パーティクルの幅。
		0.2f,								//!< パーティクルの高さ。
		D3DXVECTOR3(0.1f, 0.1f, 0.1f),		//!< 初期位置のランダム幅。
		D3DXVECTOR3(0.0f, 0.2f, 0.0f),		//!< 初速度のランダム幅。
		D3DXVECTOR3(0.0f, 0.2f, 0.0f),		//!< 速度の積分のときのランダム幅。
		{									//!< UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。		
			D3DXVECTOR4(0.0f,  0.0f, 1.0f, 1.0f),
		},
		0,									//!< UVテーブルのサイズ。
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!< 重力。	
		true,								//!< 死ぬときにフェードアウトする？
		0.5f,								//!< フェードする時間。
		1.0f,								//!< 初期アルファ値。	
		true,								//!< ビルボード？
		1.0f,								//!< 輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,									//!< 0半透明合成、1加算合成。
	};

}

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
Monster_01::Monster_01()
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
Monster_01::~Monster_01()
{
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Monster_01::Start()
{

	//スキンモデルデータをロード
	SMDResources().Load(SkinModelDataHandle_, "Monster_01.X", &Animation_);
	//モデルレンダを初期化
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//基底クラスの初期化
	IMonster::Start();

	//リムライトを有効に設定
	ModelRender_.SetRimLight(true);

	//ステートを待機に設定
	ChangeState(StateCodeE::StateWaiting);

	//待機アニメーションを開始
	PlayAnimation(AnimationWaiting,0.3f);

	//アニメーションのロープフラグを設定
	Animation_.SetAnimationLoopFlags(AnimationAttack_01, false);
	Animation_.SetAnimationLoopFlags(AnimationHit, false);
	Animation_.SetAnimationLoopFlags(AnimationDeath, false);

	//キャラクターコントローラの初期化
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	
	AnimationEvent_.Init(&ModelRender_, &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//コライダーの初期化
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	//コリジョンオブジェクトの初期化
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Monster_01::Update()
{
	//ムーブスピードを取得
	D3DXVECTOR3 MoveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateWaiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_)
		{
			//プレイヤーを発見したので追いかけ状態に変化
			ChangeState(StateCodeE::StateChase);
			break;
		}

		//スピードを緩める
		MoveSpeed *= 0.8f;

		//立ち止まり
		if (WaitingLT_ >= WaitingTime_)
		{
			//立ち止まりが終わったので徘徊開始
			ChangeState(StateCodeE::StateLoitering);

			//目的地を算出
			Destination_ = D3DXVECTOR2((Random().GetRandDouble() - 0.5f)*Distance_, (Random().GetRandDouble() - 0.5f)*Distance_) + 
				D3DXVECTOR2(DefaultPosition_.x, DefaultPosition_.z);

			//立ち止まりローカルタイムを初期化
			WaitingLT_ = 0;
			break;
		}

		//立ち止まりローカルタイムに加算
		WaitingLT_ += Time().DeltaTime();
	}
	break;
	case StateLoitering:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_)
		{
			//プレイヤーを発見したので追いかけ状態に変化
			ChangeState(StateCodeE::StateChase);
			break;
		}

		if (GetToDestinationDis() <= 0.2)
		{
			//目的地に到達したので待機状態に変化
			ChangeState(StateCodeE::StateWaiting);
			break;
		}

		//目的地までの方向ベクトルを取得
		D3DXVECTOR2 toD = GetToDestination();

		//ムーブスピードを設定
		MoveSpeed = D3DXVECTOR3(toD.x, 0, toD.y);

		//向いている方向に回転
		D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	
	}
	break;
	case StateChase:
	{

		if (GetToPlayerDis() >= toPlayerMaxDis_)
		{
			//プレイヤーを見失ったので待機状態に変化
			ChangeState(StateCodeE::StateWaiting);
			break;
		}

		if (GetToPlayerDis() <= PlayerAttackDis_)
		{
			//プレイヤーを攻撃する距離まで追い詰めたので攻撃状態に変化
			ChangeState(StateCodeE::StateAttack);
			break;
		}

		//プレイヤーへの方向ベクトルを取得
		D3DXVECTOR2 toP = GetToPlayerDir();

		//ムーブスピードを設定
		MoveSpeed = D3DXVECTOR3(toP.x, 0, toP.y);

		//向いている方向に回転
		D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	
	}
	break;
	case StateAttack:
	{
		if (!Animation_.IsPlayAnim())
		{
			//攻撃のアニメーションが終わっていれば
			if (GetToPlayerDis() > PlayerAttackDis_)
			{
				//攻撃距離から離れたので追いかけ状態に変化
				ChangeState(StateCodeE::StateChase);
				break;
			}
			else
			{
				//同じモーションをもう一度
				PlayAnimationAbs(AnimationAttack_01, 0.3f);
			}
		}

		//移動情報を削除
		MoveSpeed = D3DXVECTOR3(0, 0, 0);
	
	}
	break;
	case StateDamage:
	{
		if (!Animation_.IsPlayAnim())
		{
			//アニメーションが終わっているので追いかけ状態に変化
			ChangeState(StateChase);
			break;
		}
		
		//ダメージを受けているので動いていない
		MoveSpeed = D3DXVECTOR3(0, 0, 0);

	}
	break;
	case StateDead:
	{
		if (!Animation_.IsPlayAnim())
		{
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
		MoveSpeed = D3DXVECTOR3(0, 0, 0);

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
	IMonster::Update();

}

/**
 * アニメーション管理.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Monster_01::AnimationControl()
{
	
	//アニメーションタイム
	float AnimationTime = 1.0f / 60.0f;
	
	//状態によってアニメーションを変化
	switch (State_)
	{
	case StateWaiting:
		//待機アニメーション
		PlayAnimation(AnimationWaiting, 0.3f);
		break;

	case StateLoitering:
		//歩きアニメーション
		PlayAnimation(AnimationWalk, 0.3f);
		break;

	case StateChase:
		//走りアニメーション
		PlayAnimation(AnimationRun, 0.3f);
		break;

	case StateAttack:
		//攻撃アニメーション
		PlayAnimation(AnimationAttack_01, 0.3f);
		break;

	case StateDamage:
		//ダメージアニメーション
		PlayAnimation(AnimationHit, 0.3f);
		break;

	case StateDead:
		//死亡アニメーション
		PlayAnimation(AnimationDeath, 0.3f);
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
void Monster_01::Render()
{
	//基底クラスの描画
	IMonster::Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Monster_01::Release()
{
	//基底クラスの解放
	IMonster::Release();
}

/**
 * ダメージ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Monster_01::Damage()
{
	if (State_ == StateDead)
	{
		//死んでる。
		return;
	}

	//位置計算
	float offset = Radius_ + Height_ * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;
	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));

	//位置情報を設定
	CollisionObject_->setWorldTransform(trans);

	//当たっているコリジョンを検出
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::DamageToEnemy,
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
			CollisionWorld::DamageToEnemy,
			CollisionObject_.get()
		);
	}

	if (dmgCol != NULL && State_ != StateDamage)
	{
		//ダメージコリジョンをみつけてダメージを受けている状態でない
		
		//ダメージを食らっている。
		Hp_ -= dmgCol->Damage_;

		if (Hp_ <= 0) 
		{
			//死亡。
	
			//死亡状態に変化
			ChangeState(StateDead);

			//プレイヤーに経験値を加算
			Player_->AddExperience(100);

			//アイテムをドロップ
			DropItem* DI = NewGO<DropItem>();
			//アイテムデータの取得
			IItem* item = ItemResource().GetItem(21001);
			//ドロップアイテムの初期化
			DI->Start(item, g_MainCamera->GetCamera(), Transform_.Position_);
			

			ParticleEmitter* pe = NewGO<ParticleEmitter>();
			pe->Start(g_MainCamera->GetCamera(), DisappearanceParticle, Transform_.Position_, 8.0f);

		}
		else 
		{
			//ダメージ状態に変化
			ChangeState(StateDamage);
		}
	}

}