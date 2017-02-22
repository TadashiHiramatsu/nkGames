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
	AnimationEventGroupS AnimationEventTbl[Enemy_01::AnimationNum] =
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
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.0f, 0.1f, 1.0f, 1, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.1f, 0.1f, 1.0f, 1, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.2f, 0.1f, 1.0f, 1, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.3f, 0.1f, 1.0f, 1, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.4f, 0.1f, 1.0f, 1, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
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

	/** ���Ńp�[�e�B�N��. */
	ParticleParameterS DisappearanceParticle =
	{
		"Soul_01.png",						//!< �e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3(0.0f, 0.2f, 0.0f),		//!< �����x�B
		2.0f,								//!< �����B�P�ʂ͕b�B
		0.3f,								//!< �������ԁB�P�ʂ͕b�B
		0.2f,								//!< �p�[�e�B�N���̕��B
		0.2f,								//!< �p�[�e�B�N���̍����B
		D3DXVECTOR3(0.1f, 0.0f, 0.1f),		//!< �����ʒu�̃����_�����B
		D3DXVECTOR3(0.0f, 0.2f, 0.0f),		//!< �����x�̃����_�����B
		D3DXVECTOR3(0.0f, 0.2f, 0.0f),		//!< ���x�̐ϕ��̂Ƃ��̃����_�����B
		{									//!< UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B		
			D3DXVECTOR4(0.0f,  0.0f, 1.0f, 1.0f),
		},
		0,									//!< UV�e�[�u���̃T�C�Y�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!< �d�́B	
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
	SMDResources().Load(SkinModelDataHandle_, "Monster_01.X", &Animation_);
	//���f�������_��������
	ModelRender_.Load(SkinModelDataHandle_.GetBody());

	//���N���X�̏�����
	Enemy_01::Start();

	//�������C�g��L���ɐݒ�
	ModelRender_.SetRimLight(false);

	//�X�e�[�g��ҋ@�ɐݒ�
	ChangeState(StateCodeE::StateWaiting);

	//�ҋ@�A�j���[�V�������J�n
	PlayAnimation(AnimationWaiting,0.3f);

	//�A�j���[�V�����̃��[�v�t���O��ݒ�
	Animation_.SetAnimationLoopFlag(AnimationAttack_01, false);
	Animation_.SetAnimationLoopFlag(AnimationHit, false);
	Animation_.SetAnimationLoopFlag(AnimationDeath, false);

	//�L�����N�^�[�R���g���[���̏�����
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);
	
	AnimationEvent_.Init(&ModelRender_, &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//�R���C�_�[�̏�����
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	//�R���W�����I�u�W�F�N�g�̏�����
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

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
	D3DXVECTOR3 MoveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case StateWaiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[�𔭌������̂Œǂ�������Ԃɕω�
			ChangeState(StateCodeE::StateChase);
			break;
		}

		//�X�s�[�h���ɂ߂�
		MoveSpeed *= 0.8f;

		//�����~�܂�
		if (WaitingLT_ >= WaitingTime_)
		{
			//�����~�܂肪�I������̂Ŝp�j�J�n
			ChangeState(StateCodeE::StateLoitering);

			//�ړI�n���Z�o
			Destination_ = D3DXVECTOR2((Random::value() - 0.5f) * Distance_, (Random::value() - 0.5f) * Distance_) + 
				D3DXVECTOR2(DefaultPosition_.x, DefaultPosition_.z);

			//�����~�܂胍�[�J���^�C����������
			WaitingLT_ = 0;
			break;
		}

		//�����~�܂胍�[�J���^�C���ɉ��Z
		WaitingLT_ += Time().DeltaTime();
	}
	break;
	case StateLoitering:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[�𔭌������̂Œǂ�������Ԃɕω�
			ChangeState(StateCodeE::StateChase);
			break;
		}

		if (GetToDestinationDis() <= 0.2)
		{
			//�ړI�n�ɓ��B�����̂őҋ@��Ԃɕω�
			ChangeState(StateCodeE::StateWaiting);
			break;
		}

		//�ړI�n�܂ł̕����x�N�g�����擾
		D3DXVECTOR2 toD = GetToDestination();

		//���[�u�X�s�[�h��ݒ�
		MoveSpeed = D3DXVECTOR3(toD.x, 0, toD.y);

		//�����Ă�������ɉ�]
		D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	
	}
	break;
	case StateChase:
	{

		if (GetToPlayerDis() >= toPlayerMaxDis_ || Player_->GetDeathFlag())
		{
			//�v���C���[�����������̂őҋ@��Ԃɕω�
			ChangeState(StateCodeE::StateWaiting);
			break;
		}
		else if (GetToPlayerDis() <= PlayerAttackDis_ && !Player_->GetDeathFlag())
		{
			//�v���C���[���U�����鋗���܂Œǂ��l�߂��̂ōU����Ԃɕω�
			ChangeState(StateCodeE::StateAttack);
			break;
		}

		//�v���C���[�ւ̕����x�N�g�����擾
		D3DXVECTOR2 toP = GetToPlayerDir();

		//���[�u�X�s�[�h��ݒ�
		MoveSpeed = D3DXVECTOR3(toP.x, 0, toP.y);

		//�����Ă�������ɉ�]
		D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	
	}
	break;
	case StateAttack:
	{
		if (!Animation_.IsPlayAnim())
		{
			//�U���̃A�j���[�V�������I����Ă����
			if (GetToPlayerDis() > PlayerAttackDis_ || Player_->GetDeathFlag())
			{
				//�U���������痣�ꂽ�̂Œǂ�������Ԃɕω�
				ChangeState(StateCodeE::StateChase);
				break;
			}
			else
			{
				//�������[�V������������x
				PlayAnimationAbs(AnimationAttack_01, 0.3f);
			}
		}

		//�ړ������폜
		MoveSpeed = D3DXVECTOR3(0, 0, 0);
	
	}
	break;
	case StateDamage:
	{
		if (!Animation_.IsPlayAnim())
		{
			//�A�j���[�V�������I����Ă���̂Œǂ�������Ԃɕω�
			ChangeState(StateChase);
			break;
		}
		
		//�_���[�W���󂯂Ă���̂œ����Ă��Ȃ�
		MoveSpeed = D3DXVECTOR3(0, 0, 0);

	}
	break;
	case StateDeath:
	{
		if (!Animation_.IsPlayAnim())
		{

			if (isOnceDeath)
			{
				isOnceDeath = false;

				D3DXMATRIX posmatrix = *ModelRender_.FindBoneWorldMatrix("chestcontrol");
				D3DXVECTOR3 pos;
				pos.x = posmatrix.m[3][0];
				pos.y = posmatrix.m[3][1];
				pos.z = posmatrix.m[3][2];
				ParticleEmitter* pe = NewGO<ParticleEmitter>();
				pe->Start(g_MainCamera->GetCamera(), DisappearanceParticle, pos, 8.0f);
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
		MoveSpeed = D3DXVECTOR3(0, 0, 0);

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
	Enemy_01::Update();

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
	case StateWaiting:
		//�ҋ@�A�j���[�V����
		PlayAnimation(AnimationWaiting, 0.3f);
		break;

	case StateLoitering:
		//�����A�j���[�V����
		PlayAnimation(AnimationWalk, 0.3f);
		break;

	case StateChase:
		//����A�j���[�V����
		PlayAnimation(AnimationRun, 0.3f);
		break;

	case StateAttack:
		//�U���A�j���[�V����
		PlayAnimation(AnimationAttack_01, 0.3f);
		break;

	case StateDamage:
		//�_���[�W�A�j���[�V����
		PlayAnimation(AnimationHit, 0.3f);
		break;

	case StateDeath:
		//���S�A�j���[�V����
		PlayAnimation(AnimationDeath, 0.3f);
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
	Enemy_01::Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Release()
{
	//���N���X�̉��
	Enemy_01::Release();
}

/**
 * �_���[�W.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void Enemy_01::Damage()
{
	if (State_ == StateDeath)
	{
		//����ł�B
		return;
	}

	//�ʒu�v�Z
	float offset = Radius_ + Height_ * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;
	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));

	//�ʒu����ݒ�
	CollisionObject_->setWorldTransform(trans);

	//�������Ă���R���W���������o
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::DamageToEnemy,
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
			CollisionWorld::DamageToEnemy,
			CollisionObject_.get()
		);
	}

	if (dmgCol != NULL && State_ != StateDamage)
	{
		//�_���[�W�R���W�������݂��ă_���[�W���󂯂Ă����ԂłȂ�
		
		//�_���[�W��H����Ă���B
		Hp_ -= dmgCol->Damage_;

		if (Hp_ <= 0) 
		{
			//���S�B
	
			//���S��Ԃɕω�
			ChangeState(StateDeath);

			//�v���C���[�Ɍo���l�����Z
			Player_->AddExperience(100);

			//�A�C�e���f�[�^�̎擾
			EquipmentItem* item = new EquipmentItem(ItemDataResource().GetItem(3001));

			//�h���b�v�A�C�e���}�l�[�W���ɓo�^
			g_DropItemManager->SetDropItem(item, Transform_.Position_);

			isOnceDeath = true;

		}
		else 
		{
			//�_���[�W��Ԃɕω�
			ChangeState(StateDamage);
		}
	}

}