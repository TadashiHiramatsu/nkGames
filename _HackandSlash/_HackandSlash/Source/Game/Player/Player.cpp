/**
 * @file Source\Game\Player\Player.cpp
 *
 * プレイヤークラスの実装.
 */
#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

//無名空間
namespace
{

	/** プレイヤーのアニメーションイベントテーブル. */
	AnimationEventGroupS AnimationEventTbl[Player::AnimationNum] = 
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
		//AnimationAttack
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.0f, 1.0f, 1.0f, 11, "LeftWeapon", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.1f, 1.0f, 1.0f, 11, "LeftWeapon", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.2f, 1.0f, 1.0f, 11, "LeftWeapon", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.3f, 1.0f, 1.0f, 11, "LeftWeapon", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.4f, 1.0f, 1.0f, 11, "LeftWeapon", D3DXVECTOR3(0,0,0), 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationHit
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationDead
		{
			END_ANIMATION_EVENT(),
		}

	};

}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Start()
{
	//モデルファイルをロード
	ModelRender_.Load("StealthChar.X",&Animation_);
	//トランスフォームを設定
	ModelRender_.SetTransform(&Transform_);
	//ライトを設定
	ModelRender_.SetLight(&Light_);
	//カメラを設定
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//シャドウキャスターtrue
	ModelRender_.SetShadowCasterFlag(true);
	//シャドウレシーバーtrue
	ModelRender_.SetShadowReceiverFlag(true);

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

	//ポジションをちょっと上に
	Transform_.Position_ = D3DXVECTOR3(0, 1, 0);

	//キャラクターコントローラーの初期化
	Radius_ = 0.4f;
	Height_ = 0.3f;
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

	//ステートを待機に
	ChangeState(StateCodeE::StateWaiting);

	//アニメーションループをfalseに設定
	Animation_.SetAnimationLoopFlags(AnimationCodeE::AnimationAttack, false);
	Animation_.SetAnimationLoopFlags(AnimationCodeE::AnimationDead, false);
	Animation_.SetAnimationLoopFlags(AnimationCodeE::AnimationHit, false);

	//アニメーションイベントを初期化
	AnimationEvent_.Init(&ModelRender_, &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//シャドウを計算
	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 0.0f) + Transform_.Position_);
	Shadow().SetLightTarget(Transform_.Position_);

	//左手武器
	WeaponModelRenderL_.Load("Weapon_Scythe.X", nullptr);
	WeaponModelRenderL_.SetTransform(&WeaponTransformL_);
	WeaponModelRenderL_.SetLight(&WeaponLightL_);
	WeaponModelRenderL_.SetCamera(g_MainCamera->GetCamera());
	WeaponTransformL_.ParentMatrix_ = ModelRender_.FindBoneWorldMatrix("LeftWeapon");
	
	//右手武器
	WeaponModelRenderR_.Load("Weapon_Scythe.X", nullptr);
	WeaponModelRenderR_.SetTransform(&WeaponTransformR_);
	WeaponModelRenderR_.SetLight(&WeaponLightR_);
	WeaponModelRenderR_.SetCamera(g_MainCamera->GetCamera());
	WeaponTransformR_.ParentMatrix_ = ModelRender_.FindBoneWorldMatrix("RightWeapon");

	//コリジョン初期化
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Update()
{
	//プレイヤーパラメータの更新
	ParameterUpdate();

	//キャラクターコントローラからムーブスピードを取得
	D3DXVECTOR3 moveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case Player::StateWaiting:
	case Player::AnimationWalk:
	case Player::StateRun:
	{

		//ジャンプ処理
		if (Input().GetKeyButton(KeyCodeE::Space) && !CharacterController_.IsJump())
		{
			moveSpeed.y = 5.0f;
			CharacterController_.Jump();
		}

		//平行移動
		D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
		if (Input().GetKeyButton(KeyCodeE::W))
		{
			//正面
			move += D3DXVECTOR3(0, 0, 1);
		}
		if (Input().GetKeyButton(KeyCodeE::S))
		{
			//後ろ
			move += D3DXVECTOR3(0, 0, -1);
		}
		if (Input().GetKeyButton(KeyCodeE::A))
		{
			//左
			move += D3DXVECTOR3(-1, 0, 0);
		}
		if (Input().GetKeyButton(KeyCodeE::D))
		{
			//右
			move += D3DXVECTOR3(1, 0, 0);
		}

		//カメラの正面方向に合わせる
		D3DXVECTOR3 dirForward = g_MainCamera->GetDirectionForward();
		D3DXVECTOR3 dirRight = g_MainCamera->GetDirectionRight();
		D3DXVECTOR3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y軸はいらない。
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		//ムーブスピードを計算
		static float MOVE_SPEED = 2.0f;
		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;


		//走っている
		float len = D3DXVec3Length(&moveDir);
		if (len > 0.0f)
		{
			ChangeState(StateCodeE::StateRun);
			//正面方向に回転させている
			D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));
		}
		else
		{
			ChangeState(StateCodeE::StateWaiting);
		}

		//攻撃
		if (Input().GetMoudeButtonDown(MouseButtonE::MouseLeft) && !CharacterController_.IsJump())
		{
			ChangeState(StateCodeE::StateAttack);

		}
	}
	break;
	case Player::StateAttack:
	{
		//移動を緩める
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
		
		if (!Animation_.IsPlayAnim())
		{
			//アニメーションが終了したので待機ステートに変更
			ChangeState(StateCodeE::StateWaiting);
		}
	}
	break;
	case Player::StateDamage:
	{
		//どうしよう？
		// 強攻撃を受けたときに使うので放置
		//if (!Animation_.IsPlayAnim())
		//{
			//アニメーションが終了したので待機ステートに変更
			ChangeState(StateCodeE::StateWaiting);
		//	break;
		//}

		//移動を緩める
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
	}
	break;
	case Player::StateDead:
	{
		//死亡。移動を止める.
		moveSpeed = D3DXVECTOR3(0, 0, 0);
	}
	break;

	default:
		break;
	}

	//ムーブスピードを設定して更新
	CharacterController_.SetMoveSpeed(moveSpeed);
	CharacterController_.Update();

	//計算終了後のポジションを受け取る
	Transform_.Position_ = CharacterController_.GetPosition();

	//アニメーションの更新
	AnimationControl();

	//アニメーションイベントの更新
	AnimationEvent_.Update();

	//死んでいる又はダメージを受けている状態でなければ
	//体力回復時間を更新する
	if (State_ != StateDead && State_ != StateDamage)
	{
		RecoveryLT_ += Time().DeltaTime();
	}
	//攻撃を回避してから3秒経過で回復し始め
	if (RecoveryLT_ >= 3)
	{
		//体力が減っていれば
		if (Parameter_.MaxHp_ > Parameter_.NowHp_)
		{
			//改造の余地あり
			//2フレームに一回回復
			static bool flg = true;
			if (flg)
			{
				Parameter_.NowHp_++;
			}

			flg = !flg;
		}
	}

	//ダメージ処理の更新
	Damage();

	//トランスフォームの更新
	Transform_.Update();
	//モデルレンダーの更新
	ModelRender_.Update();

	//左手武器の更新
	WeaponTransformL_.Update();
	WeaponModelRenderL_.Update();

	//右手武器の更新
	WeaponTransformR_.Update();
	WeaponModelRenderR_.Update();
	
	//シャドウマップの更新
	Shadow().SetLightPosition(D3DXVECTOR3(-5.0f, 5.0f, -5.0f) + Transform_.Position_);
	Shadow().SetLightTarget(Transform_.Position_);

}

/**
 * 描画.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Render()
{
	//プレイヤーの描画
	ModelRender_.Render();

	//武器の描画
	WeaponModelRenderL_.Render();
	WeaponModelRenderR_.Render();

}

/**
 * 解放.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Release()
{
	ModelRender_.Release();
}

/**
 * ダメージ処理.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Damage()
{
	if (State_ == StateDead)
	{
		//死んでる...
		return;
	}

	float offset = Radius_ + Height_ * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;

	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
	CollisionObject_->setWorldTransform(trans);

	//当たっているコリジョンを検出
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::DamageToPlayer,
		CollisionObject_.get()
	);

	if (!dmgCol) 
	{
		//当たっていないので位置をずらしてもう一度
		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		CollisionObject_->setWorldTransform(trans);

		//当たっているコリジョンを検出
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::DamageToPlayer,
			CollisionObject_.get()
		);
	}

	static float InvincibleLT = 0.0f;

	//無敵状態でなければ
	if (Parameter_.InvincibleTime_ <= InvincibleLT)
	{
		//コリジョンが反応していて。攻撃を受けていなければ。
		if (dmgCol != NULL && State_ != StateDamage)
		{
			//ダメージを食らっている。
			Parameter_.NowHp_ -= dmgCol->Damage_;
			RecoveryLT_ = 0;
			
			if (Parameter_.NowHp_ <= 0)
			{
				//死亡。
				ChangeState(StateDead);
			}
			else
			{
				ChangeState(StateDamage);
			}

		}

		//無敵時間を初期化
		InvincibleLT = 0.0f;
	}
	else if(State_ != StateDamage)
	{
		//ダメージを受けていないので無敵時間を更新
		InvincibleLT += Time().DeltaTime();
	}

}

/**
 * プレイヤーパラメータの更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::ParameterUpdate()
{

	//取得経験値が必要経験値を超えていたら
	if (Parameter_.Experience_ >= Parameter_.NextLevelExperience_)
	{
		//超えたので経験値をマイナス
		Parameter_.Experience_ -= Parameter_.NextLevelExperience_;

		//必要経験値量を更新
		int a = Parameter_.NextLevelExperience_ * 1.1;
		int b = Parameter_.Level_ * 15;
		Parameter_.NextLevelExperience_ = (a + b) / 2;

		//意味ない
		Parameter_.Attack_ *= 1.1;

		//Hp上昇
		float idx = Parameter_.MaxHp_ * 1.1 - Parameter_.MaxHp_;
		Parameter_.MaxHp_ += idx;
		Parameter_.NowHp_ += idx;
		
		//レベルアップ
		Parameter_.Level_++;
	}

}

/**
 * アニメーション更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::AnimationControl()
{
	float time = 1.0f / 60.0f;
	switch (State_)
	{
	case StateWaiting:
		PlayAnimation(AnimationCodeE::AnimationWaiting, 0.1f);
		break;
	case StateWalk:
		PlayAnimation(AnimationCodeE::AnimationWalk, 0.1f);
		break;
	case StateRun:
		PlayAnimation(AnimationCodeE::AnimationRun, 0.1f);
		break;
	case StateAttack:
		PlayAnimation(AnimationCodeE::AnimationAttack, 0.1f);
		time = 1.0f / 30.0f;
		break;
	case StateDamage:
		PlayAnimation(AnimationCodeE::AnimationHit, 0.1f);
		break;
	case StateDead:
		PlayAnimation(AnimationCodeE::AnimationDead, 0.1f);
		break;
	default:
		break;
	}

	//アニメーションクラスの更新
	Animation_.Update(time);

}

/**
 * アニメーションを変更.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param animCode		  The animation code.
 * @param interpolateTime The interpolate time.
 */
void Player::PlayAnimation(AnimationCodeE animCode, float interpolateTime)
{
	if (Animation_.GetNowAnimationNo() != animCode)
	{
		Animation_.PlayAnimation(animCode, interpolateTime);
	}
}