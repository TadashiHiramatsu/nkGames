/**
 * @file Source\Game\Player\Player.cpp
 *
 * �v���C���[�N���X�̎���.
 */
#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

#include"Weapon.h"
#include"Shield.h"

//�������
namespace
{

	/** �v���C���[�̃A�j���[�V�����C�x���g�e�[�u��. */
	AnimationEventGroupS AnimationEventTbl[Player::AnimationNum] = 
	{
		//AnimationWaiting
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationRun
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_01
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.7f,	0.1f, 0.2f, 11, "CollisionPos", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.75f, 0.1f, 0.2f, 11, "CollisionPos", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.8f,	0.1f, 0.2f, 11, "CollisionPos", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.85f, 0.1f, 0.2f, 11, "CollisionPos", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.9f,	0.1f, 0.2f, 11, "CollisionPos", D3DXVECTOR3(0,0,0), 0),
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
	ModelRender_.SetLight(&Light_);
	//�J������ݒ�
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//�V���h�E�L���X�^�[true
	ModelRender_.SetShadowCasterFlag(true);
	//�V���h�E���V�[�o�[true
	ModelRender_.SetShadowReceiverFlag(true);

	//�@���}�b�v�̐ݒ�
	Normal_.Load("Player_n.png");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("Player_s.png");
	ModelRender_.SetSpecMap(&Specular_);

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

	//�|�W�V������������Ə��
	Transform_.Position_ = D3DXVECTOR3(0, 1, 0);

	//�L�����N�^�[�R���g���[���[�̏�����
	Radius_ = 0.4f;
	Height_ = 0.3f;
	CharacterController_.Init(Radius_, Height_, Transform_.Position_);

	//�X�e�[�g��ҋ@��
	ChangeState(StateCodeE::StateWaiting);

	Animation_.SetAnimationEndTime(AnimationCodeE::AnimationRun, 0.7);

	//�A�j���[�V�������[�v��false�ɐݒ�
	Animation_.SetAnimationLoopFlag(AnimationCodeE::AnimationAttack_01, false);
	Animation_.SetAnimationLoopFlag(AnimationCodeE::AnimationDeath_01, false);


	//����Ə����쐬
	Weapon* wepon = NewGO<Weapon>(1);
	wepon->Start(ModelRender_);
	Shield* shild = NewGO<Shield>(1);
	shild->Start(ModelRender_);

	//�A�j���[�V�����C�x���g��������
	AnimationEvent_.Init(&wepon->GetModelRender(), &Animation_, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	//�R���W����������
	SphereShape_.reset(new SphereCollider);
	SphereShape_->Create(Radius_);
	CollisionObject_.reset(new btCollisionObject());
	CollisionObject_->setCollisionShape(SphereShape_->GetBody());

	//�V���h�E���v�Z
	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 0.0f) + Transform_.Position_);
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
	D3DXVECTOR3 moveSpeed = CharacterController_.GetMoveSpeed();

	switch (State_)
	{
	case Player::StateWaiting:
	case Player::StateRun:
	{

		//�W�����v����
		/*if (Input().GetKeyButton(KeyCodeE::Space) && !CharacterController_.IsJump())
		{
			moveSpeed.y = 5.0f;
			CharacterController_.Jump();
		}*/

		//���s�ړ�
		D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
		move += D3DXVECTOR3(XInput().GetLeftStick().x, 0, XInput().GetLeftStick().y);

		//�J�����̐��ʕ����ɍ��킹��
		D3DXVECTOR3 dirForward = g_MainCamera->GetDirectionForward();
		D3DXVECTOR3 dirRight = g_MainCamera->GetDirectionRight();
		D3DXVECTOR3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y���͂���Ȃ��B
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		//���[�u�X�s�[�h���v�Z
		static float MOVE_SPEED = 2.0f;
		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;


		//�����Ă���
		float len = D3DXVec3Length(&moveDir);
		if (len > 0.0f)
		{
			ChangeState(StateCodeE::StateRun);
			//���ʕ����ɉ�]�����Ă���
			D3DXQuaternionRotationAxis(&Transform_.Rotation_, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));
		}
		else
		{
			ChangeState(StateCodeE::StateWaiting);
		}

		//�U��
		if (Input().GetMoudeButtonDown(MouseButtonE::MouseLeft) && !CharacterController_.IsJump())
		{
			ChangeState(StateCodeE::StateAttack);

		}
	}
	break;
	case Player::StateAttack:
	{
		//�ړ����ɂ߂�
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
		
		if (!Animation_.IsPlayAnim())
		{
			//�A�j���[�V�������I�������̂őҋ@�X�e�[�g�ɕύX
			ChangeState(StateCodeE::StateWaiting);
		}
	}
	break;
	case Player::StateDamage:
	{
		//�ǂ����悤�H
		// ���U�����󂯂��Ƃ��Ɏg���̂ŕ��u
		//if (!Animation_.IsPlayAnim())
		//{
			//�A�j���[�V�������I�������̂őҋ@�X�e�[�g�ɕύX
			ChangeState(StateCodeE::StateWaiting);
		//	break;
		//}

		//�ړ����ɂ߂�
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
	}
	break;
	case Player::StateDeath:
	{
		//���S�B�ړ����~�߂�.
		moveSpeed = D3DXVECTOR3(0, 0, 0);
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

	//�A�j���[�V�����̍X�V
	AnimationControl();

	//�A�j���[�V�����C�x���g�̍X�V
	AnimationEvent_.Update();

	//����ł��閔�̓_���[�W���󂯂Ă����ԂłȂ����
	//�̗͉񕜎��Ԃ��X�V����
	if (State_ != StateDeath && State_ != StateDamage)
	{
		RecoveryLT_ += Time().DeltaTime();
	}
	//�U����������Ă���3�b�o�߂ŉ񕜂��n��
	if (RecoveryLT_ >= 3)
	{
		//�̗͂������Ă����
		if (Parameter_.MaxHp_ > Parameter_.NowHp_)
		{
			//�����̗]�n����
			//2�t���[���Ɉ���
			static bool flg = true;
			if (flg)
			{
				Parameter_.NowHp_++;
			}

			flg = !flg;
		}
	}

	//�_���[�W�����̍X�V
	Damage();

	//�g�����X�t�H�[���̍X�V
	Transform_.Update();
	//���f�������_�[�̍X�V
	ModelRender_.Update();

	//�V���h�E�}�b�v�̍X�V
	Shadow().SetLightPosition(D3DXVECTOR3(-10.0f, 10.0f, -10.0f) + Transform_.Position_);
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
 * �_���[�W����.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Player::Damage()
{
	if (State_ == StateDeath)
	{
		//����ł�...
		return;
	}

	float offset = Radius_ + Height_ * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = Transform_.Position_;
	centerPos.y += offset;

	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
	CollisionObject_->setWorldTransform(trans);

	//�������Ă���R���W���������o
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::DamageToPlayer,
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
			CollisionWorld::DamageToPlayer,
			CollisionObject_.get()
		);
	}

	//���G��ԂłȂ����
	if (Parameter_.InvincibleTime_ <= InvincibleLT)
	{
		//�R���W�������������Ă��āB�U�����󂯂Ă��Ȃ���΁B
		if (dmgCol != NULL && State_ != StateDamage)
		{
			//�_���[�W��H����Ă���B
			Parameter_.NowHp_ -= dmgCol->Damage_;
			RecoveryLT_ = 0;
			
			if (Parameter_.NowHp_ <= 0)
			{
				//���S�B
				ChangeState(StateDeath);
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
		int a = Parameter_.NextLevelExperience_ * 1.1;
		int b = Parameter_.Level_ * 15;
		Parameter_.NextLevelExperience_ = (a + b) / 2;

		//�Ӗ��Ȃ�
		Parameter_.Attack_ *= 1.1;

		//Hp�㏸
		float idx = Parameter_.MaxHp_ * 1.1 - Parameter_.MaxHp_;
		Parameter_.MaxHp_ += idx;
		Parameter_.NowHp_ += idx;
		
		//���x���A�b�v
		Parameter_.Level_++;
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
	case StateWaiting:
		PlayAnimation(AnimationCodeE::AnimationWaiting, 0.3f);
		break;
	case StateRun:
		PlayAnimation(AnimationCodeE::AnimationRun, 0.3f);
		time = 1.0f / 15.0f;
		break;
	case StateAttack:
		PlayAnimation(AnimationCodeE::AnimationAttack_01, 0.3f);
		break;
	case StateDeath:
		PlayAnimation(AnimationCodeE::AnimationDeath_01, 0.3f);
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
	if (Animation_.GetNowAnimationNo() != animCode)
	{
		Animation_.PlayAnimation(animCode, interpolateTime);
	}
}