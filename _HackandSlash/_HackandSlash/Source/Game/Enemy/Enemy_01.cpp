/**
 * @file Source\Game\Monster\Enemy_01.cpp
 *
 * �����U��������G�N���X�̎���.
 */
#include"stdafx.h"
#include"Enemy_01.h"

/*---------------------------------------------------------------------------------------------------------*/
#include"../GameCamera.h"

#include"../../Game/Item/ItemDataResource.h"
#include"../DropItem/DropItemManager.h"

//�������
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

	/** ���Ńp�[�e�B�N��. */
	ParticleParameterS DisappearanceParticle =
	{
		"Soul_01.png",						//!< �e�N�X�`���̃t�@�C���p�X�B
		Vector3(0.0f, 0.5f, 0.0f),		//!< �����x�B
		2.0f,								//!< �����B�P�ʂ͕b�B
		0.3f,								//!< �������ԁB�P�ʂ͕b�B
		0.4f,								//!< �p�[�e�B�N���̕��B
		0.4f,								//!< �p�[�e�B�N���̍����B
		Vector3(0.3f, 0.0f, 0.3f),		//!< �����ʒu�̃����_�����B
		Vector3(0.0f, 0.3f, 0.0f),		//!< �����x�̃����_�����B
		Vector3(0.0f, 0.3f, 0.0f),		//!< ���x�̐ϕ��̂Ƃ��̃����_�����B
		{									//!< UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B		
			Vector4(0.0f,  0.0f, 1.0f, 1.0f),
		},
		0,									//!< UV�e�[�u���̃T�C�Y�B
		Vector3(0.0f, 0.0f, 0.0f),		//!< �d�́B	
		true,								//!< ���ʂƂ��Ƀt�F�[�h�A�E�g����H
		1.0f,								//!< �t�F�[�h���鎞�ԁB
		1.0f,								//!< �����A���t�@�l�B	
		true,								//!< �r���{�[�h�H
		1.0f,								//!< �P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		0,									//!< 0�����������A1���Z�����B
	};
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Start()
{

	//�X�L�����f���f�[�^�����[�h
	SMDResources().Load(SkinModelDataHandle_, "Enemy_01.X", &Animation_);
	//���f�������_��������
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//���N���X�̏�����
	IEnemy::Start();

	//�X�e�[�g��ҋ@�ɐݒ�
	ChangeState(StateCodeE::Waiting);

	//�ҋ@�A�j���[�V�������J�n
	PlayAnimation(AnimationCodeE::Waiting,0.3f);

	//�A�j���[�V�����̃��[�v�t���O��ݒ�
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Attack_01, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Hit, false);
	Animation_.SetAnimationLoopFlag((int)AnimationCodeE::Death, false);

	Radius_ = 0.3f;
	Height_ = 0.9f;
	//�L�����N�^�[�R���g���[���̏�����
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	
	AnimationEvent_.Init(&ModelRender_, &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//�R���C�_�[�̏�����
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	//�R���W�����I�u�W�F�N�g�̏�����
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

	//Hp��ݒ�.
	Hp_ = 30;

	//�v���C���[���U�����n�߂鋗����ݒ�.
	PlayerAttackDis_ = 1.0f;


}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Update()
{
	//���[�u�X�s�[�h���擾
	Vector3 MoveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateCodeE::Waiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[�𔭌������̂Œǂ�������Ԃɕω�
			ChangeState(StateCodeE::Chase);
			break;
		}

		//�X�s�[�h���ɂ߂�
		MoveSpeed.Scale(0.8f);

		//�����~�܂�
		if (WaitingLT_ >= WaitingTime_)
		{
			//�����~�܂肪�I������̂Ŝp�j�J�n
			ChangeState(StateCodeE::Loitering);

			//�ړI�n���Z�o
			Destination_ = Vector3((Random().value() - 0.5f) * Distance_, 0, (Random().value() - 0.5f) * Distance_);
			Destination_.Add(DefaultPosition_);

			//�����~�܂胍�[�J���^�C����������
			WaitingLT_ = 0;
			break;
		}

		//�����~�܂胍�[�J���^�C���ɉ��Z
		WaitingLT_ += Time().DeltaTime();
	}
	break;
	case StateCodeE::Loitering:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[�𔭌������̂Œǂ�������Ԃɕω�
			ChangeState(StateCodeE::Chase);
			break;
		}

		if (GetToDestinationDis() <= 0.2)
		{
			//�ړI�n�ɓ��B�����̂őҋ@��Ԃɕω�
			ChangeState(StateCodeE::Waiting);
			break;
		}

		//�ړI�n�܂ł̕����x�N�g�����擾
		Vector2 toD = GetToDestination();

		//���[�u�X�s�[�h��ݒ�
		MoveSpeed = Vector3(toD.x, 0, toD.y);

		//�����Ă�������ɉ�]
		Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveSpeed.x, MoveSpeed.z)) + 180.0f);
	
	}
	break;
	case StateCodeE::Chase:
	{

		if (GetToPlayerDis() >= toPlayerMaxDis_ || Player_->GetDeathFlag())
		{
			//�v���C���[�����������̂őҋ@��Ԃɕω�
			ChangeState(StateCodeE::Waiting);
			break;
		}
		else if (GetToPlayerDis() <= PlayerAttackDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[���U�����鋗���܂Œǂ��l�߂��̂ōU����Ԃɕω�
			ChangeState(StateCodeE::Attack);
			break;
		}

		//�v���C���[�ւ̕����x�N�g�����擾
		Vector2 toP = GetToPlayerDir();

		//���[�u�X�s�[�h��ݒ�
		MoveSpeed = Vector3(toP.x, 0, toP.y);

		//�����Ă�������ɉ�]
		Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveSpeed.x, MoveSpeed.z)) + 180.0f);
	
	}
	break;
	case StateCodeE::Attack:
	{
		if (!Animation_.IsPlayAnim())
		{
			//�U���̃A�j���[�V�������I����Ă����
			if (GetToPlayerDis() > PlayerAttackDis_ || Player_->GetDeathFlag())
			{
				//�U���������痣�ꂽ�̂Œǂ�������Ԃɕω�
				ChangeState(StateCodeE::Chase);
				break;
			}
			else
			{
				//�������[�V������������x
				PlayAnimationAbs(AnimationCodeE::Attack_01, 0.3f);
			}
		}

		//�ړ������폜
		MoveSpeed = Vector3::Zero;
	
	}
	break;
	case StateCodeE::Hit:
	{
		if (!Animation_.IsPlayAnim())
		{
			//�A�j���[�V�������I����Ă���̂Œǂ�������Ԃɕω�
			ChangeState(StateCodeE::Chase);
			break;
		}
		
		//�_���[�W���󂯂Ă���̂œ����Ă��Ȃ�
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

				//���Ńp�[�e�B�N���𔭐�.
				DisappearanceParticleSet("chestcontrol", DisappearanceParticle);

				//�h���b�v�A�C�e���}�l�[�W���ɓo�^
				g_DropItemManager->SetDropItem(Level_, Transform_.Position_);

			}

			//���Ŏ��Ԃ̃��[�J���^�C�������Z
			DisappearanceLT_ += Time().DeltaTime();
			//���Ŏ��Ԃ��o�߂���
			if (DisappearanceTime_ <= DisappearanceLT_)
			{
				//���X�ɓ�����
				Alpha_ = fmax(0.0f, Alpha_ - 0.01f);
				if (Alpha_ <= 0.0f)
				{
					// �A�j���[�V�������I�������̂Ńm���A�N�e�B�u�ɐݒ�
					// ���邱�Ƃō폜�����
					isActive_ = false;
					break;
				}
			}
		}
		//����ł���̂ňړ������폜
		MoveSpeed = Vector3::Zero;

	}
	break;
	
	default:
		break;
	}

	//�L�����N�^�[�R���g���[���Ɉړ�����ݒ�
	CharacterController_.SetMoveSpeed(MoveSpeed);
	//�L�����N�^�[�R���g���[���̍X�V
	CharacterController_.Update();
	
	//�v�Z�I�������|�W�V�������擾
	Transform_.Position_ = CharacterController_.GetPosition();

	//�A�j���[�V�����C�x���g���X�V
	AnimationEvent_.Update();

	//�_���[�W���X�V
	Damage();

	//�A�j���[�V�������X�V
	AnimationControl();

	//���f�������_�ɃA���t�@��ݒ�
	ModelRender_.SetAlpha(Alpha_);

	//���N���X���X�V
	IEnemy::Update();

}

/**
 * �A�j���[�V�����Ǘ�.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::AnimationControl()
{
	//�A�j���[�V�����^�C��
	float AnimationTime = Time().DeltaTime();
	
	//��Ԃɂ���ăA�j���[�V������ω�
	switch (State_)
	{
	case StateCodeE::Waiting:
		//�ҋ@�A�j���[�V����
		PlayAnimation(AnimationCodeE::Waiting, 0.3f);
		break;

	case StateCodeE::Loitering:
		//�����A�j���[�V����
		PlayAnimation(AnimationCodeE::Walk, 0.3f);
		break;

	case StateCodeE::Chase:
		//����A�j���[�V����
		PlayAnimation(AnimationCodeE::Run, 0.3f);
		break;

	case StateCodeE::Attack:
		//�U���A�j���[�V����
		PlayAnimation(AnimationCodeE::Attack_01, 0.3f);
		break;

	case StateCodeE::Hit:
		//�_���[�W�A�j���[�V����
		PlayAnimation(AnimationCodeE::Hit, 0.3f);
		break;

	case StateCodeE::Death:
		//���S�A�j���[�V����
		PlayAnimation(AnimationCodeE::Death, 0.3f);
		break;

	default:
		break;
	}

	//�A�j���[�V�����̍X�V
	Animation_.Update(AnimationTime);

}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Render()
{
	//���N���X�̕`��
	IEnemy::Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Release()
{
}

/**
 * �_���[�W.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Damage()
{
	if (State_ == StateCodeE::Death)
	{
		//����ł�B
		return;
	}

	//�ʒu�v�Z
	float offset = Radius_ + Height_ * 0.5f;
	Vector3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;
	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));

	//�ʒu����ݒ�
	CollisionObject_->setWorldTransform(trans);

	//�������Ă���R���W���������o
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::AttributeE::DamageToEnemy,
		CollisionObject_.get()
	);

	if (!dmgCol)
	{
		//�������Ă��Ȃ�

		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		//�ʒu�����X�V
		CollisionObject_->setWorldTransform(trans);
		
		//������x�������Ă���R���W���������o
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::AttributeE::DamageToEnemy,
			CollisionObject_.get()
		);
	}

	if (dmgCol != NULL && State_ != StateCodeE::Hit)
	{
		//�_���[�W�R���W�������݂��ă_���[�W���󂯂Ă����ԂłȂ�
		
		//�_���[�W��H����Ă���B
		Hp_ -= dmgCol->Damage_;

		if (Hp_ <= 0) 
		{
			//���S�B
	
			//���S��Ԃɕω�
			ChangeState(StateCodeE::Death);

			//�v���C���[�Ɍo���l�����Z
			Player_->AddExperience(2);

			//�L�����N�^�[�R���g���[���̍��̂��폜
			CharacterController_.RemoveRigidBody();

			
			isOnceDeath_ = true;

		}
		else 
		{
			//�q�b�g��Ԃɕω�
			ChangeState(StateCodeE::Hit);
		}

	}

}