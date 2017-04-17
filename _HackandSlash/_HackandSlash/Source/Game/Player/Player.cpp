/**
 * @file Source\Game\Player\Player.cpp
 *
 * �v���C���[�N���X�̎���.
 */
#include"stdafx.h"
#include"Player.h"

#include"../GameCamera.h"
#include"../GameLight.h"

#include"EquipmentWeapon.h"
#include"EquipmentShield.h"

#include"../Window/MenuWindow/MenuSystem.h"
#include"../DropItem/DropItemManager.h"

//�������
namespace
{

	/** �v���C���[�̃A�j���[�V�����C�x���g�e�[�u��. */
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
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Start()
{
	//���f���t�@�C�������[�h
	ModelRender_.Load("Player.X",&Animation_);
	//�g�����X�t�H�[����ݒ�
	ModelRender_.SetTransform(&Transform_);
	//���C�g��ݒ�
	ModelRender_.SetLight(g_GameLight->GetLight());
	//�J������ݒ�
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//�V���h�E�L���X�^�[true
	ModelRender_.SetShadowCasterFlag(true);
	//�V���h�E���V�[�o�[true
	ModelRender_.SetShadowReceiverFlag(true);

	//�@���}�b�v�̐ݒ�
	Normal_.Load("Paladin_normal.png");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("Paladin_specular.png");
	ModelRender_.SetSpecMap(&Specular_);

	//�|�W�V������������Ə��
	RespawnPosition_ = Vector3(65, 5, -65);
	Transform_.Position_ = RespawnPosition_;

	//�L�����N�^�[�R���g���[���[�̏�����
	//������Ӓ����Ȃ����
	Radius_ = 0.3f;
	Height_ = 1.0f;
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	CharacterController_.SetGravity(-9.8f * 2);

	//�X�e�[�g��ҋ@��
	ChangeState(StateCodeE::Waiting);

	Animation_.SetAnimationEndTime((int)AnimationCodeE::Run, 0.7);

	//�A�j���[�V�������[�v��false�ɐݒ�
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_01, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_08, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Death_01, false);

	NextAttackAnimCode_ = ReqAttackAnimCode_ = AnimationCodeE::Invalid;

	//����Ə����쐬
	EquipmentWeapon* wepon = NewGO<EquipmentWeapon>(1);
	wepon->Start(ModelRender_);
	EquipmentShield* shild = NewGO<EquipmentShield>(1);
	shild->Start(ModelRender_);

	//�A�j���[�V�����C�x���g��������
	AnimationEvent_.Init(&wepon->GetModelRender(), &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//�R���W����������
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

	//�p�����[�^�̏�����.
	Parameter_.Continue();

	//�V���h�E���v�Z
	Vector3 ShadowLightPos;
	ShadowLightPos.Add(Vector3(-10.0f, 10.0f, -10.0f), Transform_.Position_);
	Shadow().SetLightPosition(ShadowLightPos);
	Shadow().SetLightTarget(Transform_.Position_);
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Update()
{
	//�v���C���[�p�����[�^�̍X�V
	ParameterUpdate();

	//�L�����N�^�[�R���g���[�����烀�[�u�X�s�[�h���擾
	Vector3 moveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateCodeE::Waiting:
	case StateCodeE::Walk:
	case StateCodeE::Run:
	{

		//�W�����v����
		if (Input().GetKeyButton(KeyCodeE::Space))
		{
			moveSpeed.y += 15.0f;
			CharacterController_.Jump();
		}

		//���s�ړ�
		Vector3 move = Vector3::Zero;

		if (!g_MenuSystem->GetEffectiveness())
		{
			//���j���[���\������Ă��Ȃ���Έړ�������.
			move.Add(Vector3(XInput().GetLeftStick().x, 0, XInput().GetLeftStick().y));
		}

		//�J�����̐��ʕ����ɍ��킹��
		Vector3 dirForward = g_MainCamera->GetDirectionForward();
		Vector3 dirRight = g_MainCamera->GetDirectionRight();
		Vector3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y���͂���Ȃ��B
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		//���[�u�X�s�[�h���v�Z
		static float MOVE_SPEED = 70.0f;
		moveDir.Scale(MOVE_SPEED * Time().DeltaTime());
		moveSpeed = moveDir;

		float len = moveDir.Length();
		if (len > 0.2f)
		{
			//�����Ă���.

			//�����Ԃɕω�.
			ChangeState(StateCodeE::Run);
			//���ʕ����ɉ�]�����Ă���
			Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(moveDir.x, moveDir.z)) + 180.0f);
	
		}
		else if (len > 0.0f)
		{
			//�����Ă���.

			//������Ԃɕω�.
			ChangeState(StateCodeE::Walk);
			//���ʕ����ɉ�]�����Ă���
			Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(moveDir.x, moveDir.z)) + 180.0f);

		}
		else
		{
			ChangeState(StateCodeE::Waiting);
		}

		//�U��
		//��΂ǂ��ɂ������ق�������.
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
		//�ړ����ɂ߂�
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;

		int currentAnimCode = Animation_.GetNowAnimationNo();

		if (!Animation_.IsPlayAnim() && NextAttackAnimCode_ == AnimationCodeE::Invalid)
		{
			//�A�j���[�V�������I������
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
		//�ǂ����悤�H
		// ���U�����󂯂��Ƃ��Ɏg���̂ŕ��u
		//if (!Animation_.IsPlayAnim())
		//{
			//�A�j���[�V�������I�������̂őҋ@�X�e�[�g�ɕύX
			ChangeState(StateCodeE::Waiting);
		//	break;
		//}

		//�ړ����ɂ߂�
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
	}
	break;
	case StateCodeE::Death:
	{
		//���S�B�ړ����~�߂�.
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

	//���[�u�X�s�[�h��ݒ肵�čX�V
	CharacterController_.SetMoveSpeed(moveSpeed);
	CharacterController_.Update();

	//�v�Z�I����̃|�W�V�������󂯎��
	Transform_.Position_ = CharacterController_.GetPosition();

	{
		int animnum = (int)AnimationCodeE::Attack_01;
		AnimationEventTbl[animnum].Event_[0].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[1].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[2].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[3].iArg_[0] = Parameter_.Attack_;
		AnimationEventTbl[animnum].Event_[4].iArg_[0] = Parameter_.Attack_;

		animnum = (int)AnimationCodeE::Attack_08;
		//���U���ɂ��Ă݂�.
		AnimationEventTbl[animnum].Event_[0].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[1].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[2].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[3].iArg_[0] = Parameter_.Attack_ * 1.2;
		AnimationEventTbl[animnum].Event_[4].iArg_[0] = Parameter_.Attack_ * 1.2;
	}

	//�A�j���[�V�����̍X�V
	AnimationControl();

	//�A�j���[�V�����C�x���g�̍X�V
	AnimationEvent_.Update();

	//����ł��閔�̓_���[�W���󂯂Ă����ԂłȂ����
	//�̗͉񕜎��Ԃ��X�V����
	if (State_ != StateCodeE::Death && State_ != StateCodeE::Damage)
	{
		RecoveryLT_ += Time().DeltaTime();
	}

	//�U����������Ă���3�b�o�߂ŉ񕜂��n��
	if (RecoveryLT_ >= 3.0f)
	{
		//�̗͂������Ă����
		if (Parameter_.MaxHp_ > Parameter_.NowHp_)
		{
			//�����̗]�n����
			Parameter_.NowHp_ = min(Parameter_.MaxHp_, Parameter_.NowHp_ + (RecoveryLT_ - 3.0f) * 1.2f);
		}
	}

	//�_���[�W�����̍X�V
	Damage();

	//�g�����X�t�H�[���̍X�V
	Transform_.Update();
	//���f�������_�[�̍X�V
	ModelRender_.Update();

	//�V���h�E�}�b�v�̍X�V
	Vector3 ShadowLightPos;
	ShadowLightPos.Add(Vector3(-10.0f, 10.0f, -10.0f), Transform_.Position_);
	Shadow().SetLightPosition(ShadowLightPos);
	Shadow().SetLightTarget(Transform_.Position_);

}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Render()
{
	//�v���C���[�̕`��
	ModelRender_.Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Release()
{
	ModelRender_.Release();
}

/**
* �Z�[�u.
*/
void Player::Save()
{
	Parameter_.Save();
	//�ЂƂ܂�.
	InventoryManager().Save();
}

/**
 * �_���[�W����.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Damage()
{
	if (State_ == StateCodeE::Death)
	{
		//����ł�...
		return;
	}

	//���G��ԂłȂ����
	if (Parameter_.InvincibleTime_ <= InvincibleLT)
	{

		float offset = Radius_ + Height_ * 0.5f;
		Vector3 centerPos;
		centerPos = Transform_.Position_;
		centerPos.y += offset;

		btTransform trans;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		CollisionObject_->setWorldTransform(trans);

		//�������Ă���R���W���������o
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::AttributeE::DamageToPlayer,
			CollisionObject_.get()
		);

		if (!dmgCol)
		{
			//�������Ă��Ȃ��̂ňʒu�����炵�Ă�����x
			centerPos.y += offset;
			trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
			CollisionObject_->setWorldTransform(trans);

			//�������Ă���R���W���������o
			const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
				CollisionWorld::AttributeE::DamageToPlayer,
				CollisionObject_.get()
			);
		}


		//�R���W�������������Ă��āB�U�����󂯂Ă��Ȃ���΁B
		if (dmgCol != NULL && State_ != StateCodeE::Damage)
		{
			//�_���[�W��H����Ă���B
			Parameter_.NowHp_ -= dmgCol->Damage_;
			RecoveryLT_ = 0;

			if (Parameter_.NowHp_ <= 0)
			{
				//���S�B
				ChangeState(StateCodeE::Death);
			}
			else
			{
				//���G���Ԃ�������
				InvincibleLT = 0.0f;
				//ChangeState(StateDamage);
			}
		}
	}
	else
	{
		//�_���[�W���󂯂Ă��Ȃ��̂Ŗ��G���Ԃ��X�V
		InvincibleLT += Time().DeltaTime();
	}

}

/**
 * �v���C���[�p�����[�^�̍X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::ParameterUpdate()
{
	//�擾�o���l���K�v�o���l�𒴂��Ă�����
	if (Parameter_.Experience_ >= Parameter_.NextLevelExperience_)
	{
		//�������̂Ōo���l���}�C�i�X
		Parameter_.Experience_ -= Parameter_.NextLevelExperience_;

		//�K�v�o���l�ʂ��X�V
		int aE = Parameter_.NextLevelExperience_ * 1.2;
		int bE = Parameter_.Level_ * 10;
		Parameter_.NextLevelExperience_ = (aE + bE) / 2;

		//�Ӗ��Ȃ�
		Parameter_.Attack_ *= 1.2;

		//Hp�㏸
		int aH = Parameter_.MaxHp_ * 1.1;
		int bH = Parameter_.Level_ * 100;
		int idx = (aH + bH) / 2;
		Parameter_.MaxHp_ = idx;
		Parameter_.NowHp_ = idx;
		
		//���x���A�b�v
		Parameter_.Level_++;

		SoundSource* levelup = NewGO<SoundSource>();
		levelup->InitOnMemory("Game/LevelUp");
		levelup->Play();
	}

}

/**
 * �A�j���[�V�����X�V.
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
			//�U���J�n�B
			PlayAnimation(NextAttackAnimCode_, 0.3f);
			ReqAttackAnimCode_ = NextAttackAnimCode_;
			NextAttackAnimCode_ = AnimationCodeE::Invalid;
		}
		else if (NextAttackAnimCode_ != AnimationCodeE::Invalid) {
			//�A���̃A�j���[�V���������N�G�X�g�L���[�ɐςށB
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

	//�A�j���[�V�����N���X�̍X�V
	Animation_.Update(time);

}

/**
 * �A�j���[�V������ύX.
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
