/**
 * @file Source\Game\Player\Player.cpp
 *
 * プレイヤークラスの実装.
 */
#include"stdafx.h"
#include"Player.h"

#include"../GameCamera.h"
#include"../GameLight.h"

#include"EquipmentWeapon.h"
#include"EquipmentShield.h"

#include"../Window/MenuWindow/MenuSystem.h"
#include"../DropItem/DropItemManager.h"

//無名空間
namespace
{

	/** プレイヤーのアニメーションイベントテーブル. */
	AnimationEventGroupS AnimationEventTbl[(int)Player::AnimationCodeE::AnimationNum] = 
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
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.5f,	0.1f, 0.8f, 11, "CollisionPos", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.55f, 0.1f, 0.8f, 11, "CollisionPos", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.6f,	0.1f, 0.8f, 11, "CollisionPos", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.65f, 0.1f, 0.8f, 11, "CollisionPos", Vector3::Zero, 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.7f,	0.1f, 0.8f, 11, "CollisionPos", Vector3::Zero, 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_08
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.5f,	0.1f, 1.2f, 11, "CollisionPos", Vector3::Zero, 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationDeath_01
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
	ModelRender_.Load("Player.X",&Animation_);
	//トランスフォームを設定
	ModelRender_.SetTransform(&Transform_);
	//ライトを設定
	ModelRender_.SetLight(g_GameLight->GetLight());
	//カメラを設定
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//シャドウキャスターtrue
	ModelRender_.SetShadowCasterFlag(true);
	//シャドウレシーバーtrue
	ModelRender_.SetShadowReceiverFlag(true);

	//法線マップの設定
	Normal_.Load("Paladin_normal.png");
	ModelRender_.SetNormalMap(&Normal_);

	//スペキュラマップの設定
	Specular_.Load("Paladin_specular.png");
	ModelRender_.SetSpecMap(&Specular_);

	//ポジションをちょっと上に
	RespawnPosition_ = Vector3(65, 5, -65);
	Transform_.Position_ = RespawnPosition_;

	//キャラクターコントローラーの初期化
	//ここら辺直さなきゃな
	Radius_ = 0.3f;
	Height_ = 1.0f;
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	CharacterController_.SetGravity(-9.8f * 2);

	//ステートを待機に
	ChangeState(StateCodeE::Waiting);

	Animation_.SetAnimationEndTime((int)AnimationCodeE::Run, 0.7);

	//アニメーションループをfalseに設定
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_01, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_08, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Death_01, false);

	NextAttackAnimCode_ = ReqAttackAnimCode_ = AnimationCodeE::Invalid;

	//武器と盾を作成
	EquipmentWeapon* wepon = NewGO<EquipmentWeapon>(1);
	wepon->Start(ModelRender_);
	EquipmentShield* shild = NewGO<EquipmentShield>(1);
	shild->Start(ModelRender_);

	//アニメーションイベントを初期化
	AnimationEvent_.Init(&wepon->GetModelRender(), &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//コリジョン初期化
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

	//パラメータの初期化.
	Parameter_.Continue();

	//シャドウを計算
	Vector3 ShadowLightPos;
	ShadowLightPos.Add(Vector3(-10.0f, 10.0f, -10.0f), Transform_.Position_);
	Shadow().SetLightPosition(ShadowLightPos);
	Shadow().SetLightTarget(Transform_.Position_);
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
	Vector3 moveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateCodeE::Waiting:
	case StateCodeE::Walk:
	case StateCodeE::Run:
	{

		//ジャンプ処理
		if (Input().GetKeyButton(KeyCodeE::Space))
		{
			moveSpeed.y += 15.0f;
			CharacterController_.Jump();
		}

		//平行移動
		Vector3 move = Vector3::Zero;

		if (!g_MenuSystem->GetEffectiveness())
		{
			//メニューが表示されていなければ移動させる.
			move.Add(Vector3(XInput().GetLeftStick().x, 0, XInput().GetLeftStick().y));
		}

		//カメラの正面方向に合わせる
		Vector3 dirForward = g_MainCamera->GetDirectionForward();
		Vector3 dirRight = g_MainCamera->GetDirectionRight();
		Vector3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y軸はいらない。
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		//ムーブスピードを計算
		static float MOVE_SPEED = 70.0f;
		moveDir.Scale(MOVE_SPEED * Time().DeltaTime());
		moveSpeed = moveDir;

		float len = moveDir.Length();
		if (len > 0.2f)
		{
			//走っている.

			//走り状態に変化.
			ChangeState(StateCodeE::Run);
			//正面方向に回転させている
			Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(moveDir.x, moveDir.z)) + 180.0f);
	
		}
		else if (len > 0.0f)
		{
			//歩いている.

			//歩き状態に変化.
			ChangeState(StateCodeE::Walk);
			//正面方向に回転させている
			Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(moveDir.x, moveDir.z)) + 180.0f);

		}
		else
		{
			ChangeState(StateCodeE::Waiting);
		}

		//攻撃
		//絶対どうにかしたほうがいい.
		if(XInput().IsTrigger(ButtonE::A) && 
			!CharacterController_.IsJump() && 
			!g_MenuSystem->GetEffectiveness() && 
			!g_DropItemManager->GetisGetItem())
		{
			NextAttackAnimCode_ = AnimationCodeE::Attack_01;
			ChangeState(StateCodeE::Attack);
		}

	}
	break;
	case StateCodeE::Attack:
	{
		//移動を緩める
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;

		int currentAnimCode = Animation_.GetNowAnimationNo();

		if (!Animation_.IsPlayAnim() && NextAttackAnimCode_ == AnimationCodeE::Invalid)
		{
			//アニメーションが終了した
			ChangeState(StateCodeE::Waiting);
		}
		else if (XInput().IsTrigger(ButtonE::A) &&
			currentAnimCode >= (int)AnimationCodeE::Attack_Start &&
			currentAnimCode < (int)AnimationCodeE::Attack_End &&
			currentAnimCode == (int)ReqAttackAnimCode_)
		{
			NextAttackAnimCode_ = (AnimationCodeE)(currentAnimCode + 1);
		}

	}
	break;
	case StateCodeE::Damage:
	{
		//どうしよう？
		// 強攻撃を受けたときに使うので放置
		//if (!Animation_.IsPlayAnim())
		//{
			//アニメーションが終了したので待機ステートに変更
			ChangeState(StateCodeE::Waiting);
		//	break;
		//}

		//移動を緩める
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
	}
	break;
	case StateCodeE::Death:
	{
		//死亡。移動を止める.
		moveSpeed = Vector3(0, 0, 0);

		if (XInput().IsTrigger(ButtonE::A))
		{
			Respawn();
		}
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

	{
		int animnum = (int)AnimationCodeE::Attack_01;
		AnimationEventTbl[animnum].Event_[0].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[1].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[2].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[3].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[4].iArg_[0] = Parameter_.Attack_;

		animnum = (int)AnimationCodeE::Attack_08;
		//強攻撃にしてみた.
		AnimationEventTbl[animnum].Event_[0].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[1].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[2].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[3].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[4].iArg_[0] = Parameter_.Attack_ * 1.2;
	}

	//アニメーションの更新
	AnimationControl();

	//アニメーションイベントの更新
	AnimationEvent_.Update();

	//死んでいる又はダメージを受けている状態でなければ
	//体力回復時間を更新する
	if (State_ != StateCodeE::Death && State_ != StateCodeE::Damage)
	{
		RecoveryLT_ += Time().DeltaTime();
	}

	//攻撃を回避してから3秒経過で回復し始め
	if (RecoveryLT_ >= 3.0f)
	{
		//体力が減っていれば
		if (Parameter_.MaxHp_ > Parameter_.NowHp_)
		{
			//改造の余地あり
			Parameter_.NowHp_ = min(Parameter_.MaxHp_, Parameter_.NowHp_ + (RecoveryLT_ - 3.0f) * 1.2f);
		}
	}

	//ダメージ処理の更新
	Damage();

	//トランスフォームの更新
	Transform_.Update();
	//モデルレンダーの更新
	ModelRender_.Update();

	//シャドウマップの更新
	Vector3 ShadowLightPos;
	ShadowLightPos.Add(Vector3(-10.0f, 10.0f, -10.0f), Transform_.Position_);
	Shadow().SetLightPosition(ShadowLightPos);
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
* セーブ.
*/
void Player::Save()
{
	Parameter_.Save();
	//ひとまず.
	InventoryManager().Save();
}

/**
 * ダメージ処理.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Damage()
{
	if (State_ == StateCodeE::Death)
	{
		//死んでる...
		return;
	}

	//無敵状態でなければ
	if (Parameter_.InvincibleTime_ <= InvincibleLT)
	{

		float offset = Radius_ + Height_ * 0.5f;
		Vector3 centerPos;
		centerPos = Transform_.Position_;
		centerPos.y += offset;

		btTransform trans;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		CollisionObject_->setWorldTransform(trans);

		//当たっているコリジョンを検出
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::AttributeE::DamageToPlayer,
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
				CollisionWorld::AttributeE::DamageToPlayer,
				CollisionObject_.get()
			);
		}


		//コリジョンが反応していて。攻撃を受けていなければ。
		if (dmgCol != NULL && State_ != StateCodeE::Damage)
		{
			//ダメージを食らっている。
			Parameter_.NowHp_ -= dmgCol->Damage_;
			RecoveryLT_ = 0;

			if (Parameter_.NowHp_ <= 0)
			{
				//死亡。
				ChangeState(StateCodeE::Death);
			}
			else
			{
				//無敵時間を初期化
				InvincibleLT = 0.0f;
				//ChangeState(StateDamage);
			}
		}
	}
	else
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
		int aE = Parameter_.NextLevelExperience_ * 1.2;
		int bE = Parameter_.Level_ * 10;
		Parameter_.NextLevelExperience_ = (aE + bE) / 2;

		//意味ない
		Parameter_.Attack_ *= 1.2;

		//Hp上昇
		int aH = Parameter_.MaxHp_ * 1.1;
		int bH = Parameter_.Level_ * 100;
		int idx = (aH + bH) / 2;
		Parameter_.MaxHp_ = idx;
		Parameter_.NowHp_ = idx;
		
		//レベルアップ
		Parameter_.Level_++;

		SoundSource* levelup = NewGO<SoundSource>();
		levelup->InitOnMemory("Game/LevelUp");
		levelup->Play();
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
	float time = Time().DeltaTime();

	switch (State_)
	{
	case StateCodeE::Waiting:
		PlayAnimation(AnimationCodeE::Idol, 0.3f);
		break;
	case StateCodeE::Walk:
		PlayAnimation(AnimationCodeE::Walk, 0.3f);
		break;
	case StateCodeE::Run:
		PlayAnimation(AnimationCodeE::Run, 0.4f);
		time = 1.0f / 15.0f;
		break;
	case StateCodeE::Attack:
	{
		if (NextAttackAnimCode_ == AnimationCodeE::Attack_Start) {
			//攻撃開始。
			PlayAnimation(NextAttackAnimCode_, 0.3f);
			ReqAttackAnimCode_ = NextAttackAnimCode_;
			NextAttackAnimCode_ = AnimationCodeE::Invalid;
		}
		else if (NextAttackAnimCode_ != AnimationCodeE::Invalid) {
			//連撃のアニメーションをリクエストキューに積む。
			Animation_.PlayAnimationQueue((int)NextAttackAnimCode_, 0.5f);
			ReqAttackAnimCode_ = NextAttackAnimCode_;
			NextAttackAnimCode_ = AnimationCodeE::Invalid;
		}
	}
	break;
	case StateCodeE::Death:
		PlayAnimation(AnimationCodeE::Death_01, 0.3f);
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
	if (Animation_.GetNowAnimationNo() != (int)animCode)
	{
		Animation_.PlayAnimation((int)animCode, interpolateTime);
	}
}
