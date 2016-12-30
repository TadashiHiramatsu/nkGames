#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

namespace
{
	AnimationEventGroup AnimationEventTbl[Player::AnimationNum]
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

	SParicleEmitParameter AttackParticle
	{
		"fire_02.png",						//!<�e�N�X�`���̃t�@�C���p�X�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<�����x�B
		0.1f,								//!<�����B�P�ʂ͕b�B
		0.001f,								//!<�������ԁB�P�ʂ͕b�B
		0.5f,								//!<�p�[�e�B�N���̕��B
		0.5f,								//!<�p�[�e�B�N���̍����B
		D3DXVECTOR3(0.05f, 0.05f, 0.05f),		//!<�����ʒu�̃����_�����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<�����x�̃����_�����B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{									//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B		
			D3DXVECTOR4(0.0f,  0.0f, 1.0f, 1.0f),
			D3DXVECTOR4(0.25f, 0.0f, 0.5f,  0.5f),
			D3DXVECTOR4(0.5f,  0.0f, 0.75f, 0.5f),
			D3DXVECTOR4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		0,									//!<UV�e�[�u���̃T�C�Y�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//!<�d�́B	
		true,								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.5f,								//!<�t�F�[�h���鎞�ԁB
		1.0f,								//!<�����A���t�@�l�B	
		true,								//!<�r���{�[�h�H
		1.0f,								//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,									//!<0�����������A1���Z�����B
	};
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	Model.Load("StealthChar.X",&Animation);
	Model.SetTransform(&transform);
	Model.SetLight(&Light);
	Model.SetCamera(g_MainCamera->GetCamera());
	Model.SetShadowCasterFlag(true);
	Model.SetShadowReceiverFlag(true);

	transform.Position = D3DXVECTOR3(0, 1, 0);

	Radius = 0.4f;
	Height = 0.3f;
	CharacterController.Init(Radius, Height, transform.Position);
	ChangeState(StateCode::StateWaiting);
	Animation.SetAnimationLoopFlags(AnimationCode::AnimationAttack, false);
	Animation.SetAnimationLoopFlags(AnimationCode::AnimationDead, false);
	Animation.SetAnimationLoopFlags(AnimationCode::AnimationHit, false);

	animEvent.Init(&Model,&Animation,AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 6.0f) + transform.Position);
	Shadow().SetLightTarget(transform.Position);

	//mParticle = Model.FindBoneWorldMatrix("Bip01_R_Finger0");
	//ParticlePos = D3DXVECTOR3(mParticle->m[3][0], mParticle->m[3][1], mParticle->m[3][2]);

	//Particle.Init(MainCamera.GetCamera(), AttackParticle, &ParticlePos);

	//���蕐��
	LWeaponModel.Load("Weapon_Scythe.X",nullptr);
	LWeaponModel.SetTransform(&LWeaponTransform);
	LWeaponModel.SetLight(&LWeaponLight);
	LWeaponModel.SetCamera(g_MainCamera->GetCamera());
	LWeaponTransform.ParentMatrix = Model.FindBoneWorldMatrix("LeftWeapon");
	//�E�蕐��
	RWeaponModel.Load("Weapon_Scythe.X", nullptr);
	RWeaponModel.SetTransform(&RWeaponTransform);
	RWeaponModel.SetLight(&RWeaponLight);
	RWeaponModel.SetCamera(g_MainCamera->GetCamera());
	RWeaponTransform.ParentMatrix = Model.FindBoneWorldMatrix("RightWeapon");

	sphereShape.reset(new CSphereCollider);
	sphereShape->Create(Radius);
	collisionObject.reset(new btCollisionObject());
	collisionObject->setCollisionShape(sphereShape->GetBody());

	TF.Create(50,20,TestFont::FontWeights::NORMAL);
}

void Player::Update()
{
	ParameterUpdate();

	D3DXVECTOR3 moveSpeed = CharacterController.GetMoveSpeed();

	switch (State)
	{
	case Player::StateWaiting:
	case Player::AnimationWalk:
	case Player::StateRun:
	{

		//�W�����v����
		if (Input.GetKeyButton(KeyCode::Space) && !CharacterController.IsJump())
		{
			moveSpeed.y = 5.0f;
			CharacterController.Jump();
		}


		D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
		if (Input.GetKeyButton(KeyCode::W))
		{
			move += D3DXVECTOR3(0, 0, 1);
		}
		if (Input.GetKeyButton(KeyCode::S))
		{
			move += D3DXVECTOR3(0, 0, -1);
		}
		if (Input.GetKeyButton(KeyCode::A))
		{
			move += D3DXVECTOR3(-1, 0, 0);
		}
		if (Input.GetKeyButton(KeyCode::D))
		{
			move += D3DXVECTOR3(1, 0, 0);
		}

		//�J�����̐��ʕ����ɍ��킹��
		D3DXVECTOR3 dirForward = g_MainCamera->GetDirectionForward();
		D3DXVECTOR3 dirRight = g_MainCamera->GetDirectionRight();
		D3DXVECTOR3 moveDir;
		moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
		moveDir.y = 0.0f;	//Y���͂���Ȃ��B
		moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

		static float MOVE_SPEED = 4.0f;
		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;


		//�����Ă���
		float len = D3DXVec3Length(&moveDir);
		if (len > 0.0f)
		{
			ChangeState(StateCode::StateRun);
			D3DXQuaternionRotationAxis(&transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));
		}
		else
		{
			ChangeState(StateCode::StateWaiting);
		}

		if (Input.GetKeyButton(KeyCode::Shift_L) && !CharacterController.IsJump())
		{
			ChangeState(StateCode::StateAttack);
			//Particle.SetCreate(true);
		}
	}
	break;
	case Player::StateAttack:
	{
		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
		
		if (!Animation.IsPlayAnim())
		{
			ChangeState(StateCode::StateWaiting);
			//Particle.SetCreate(false);
		}
	}
	break;
	case Player::StateDamage:
	{
		if (!Animation.IsPlayAnim())
		{
			ChangeState(StateWaiting);
			break;
		}

		moveSpeed.x *= 0.8f;
		moveSpeed.z *= 0.8f;
	}
	break;
	case Player::StateDead:
	{
		moveSpeed = D3DXVECTOR3(0, 0, 0);
	}
	break;
	default:
		break;
	}

	CharacterController.SetMoveSpeed(moveSpeed);
	CharacterController.Update();

	transform.Position = CharacterController.GetPosition();

	AnimationControl();

	animEvent.Update();

	Damage();

	transform.Update();
	Model.Update();
	LWeaponTransform.Update();
	LWeaponModel.Update();
	RWeaponTransform.Update();
	RWeaponModel.Update();
	
	//ParticlePos = D3DXVECTOR3(mParticle->m[3][0], mParticle->m[3][1], mParticle->m[3][2]);
	//Particle.Update();

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 5.0f, 6.0f) + transform.Position);
	Shadow().SetLightTarget(transform.Position);
}

void Player::Render()
{
	Model.Render();
	LWeaponModel.Render();
	RWeaponModel.Render();
	//Particle.Render();

	TF.Render("Level",PP.Level);
}

void Player::Release()
{
	Model.Release();
}

void Player::Damage()
{
	if (State == StateDead)
	{
		//����ł�...
		return;
	}
	float offset = Radius + Height * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = transform.Position;
	centerPos.y += offset;

	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
	collisionObject->setWorldTransform(trans);

	//�������Ă���R���W���������o
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::enDamageToPlayer,
		collisionObject.get()
	);

	if (!dmgCol) {
		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		collisionObject->setWorldTransform(trans);
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::enDamageToPlayer,
			collisionObject.get()
		);
	}
	if (PP.HitTime <= LocalTime)
	{
		if (dmgCol != NULL && State != StateDamage) {
			//�_���[�W��H����Ă���B
			PP.NowHp -= dmgCol->Damage;
			if (PP.NowHp <= 0) {
				//���S�B
				ChangeState(StateDead);
			}
			else
			{
				ChangeState(StateDamage);
			}
		}
		LocalTime = 0;
	}
	else if(State != StateDamage)
	{
		LocalTime += Time().DeltaTime();
	}
}

void Player::ParameterUpdate()
{
	if (PP.Experience >= PP.NextLevelExperience)
	{
		PP.Experience -= PP.NextLevelExperience;

		int a = PP.NextLevelExperience * 1.1;
		int b = PP.Level * 15;

		PP.NextLevelExperience = (a + b) / 2;

		//�Ӗ��Ȃ�
		PP.Attack *= 1.1;

		PP.MaxHp *= 1.1;

		PP.Level++;
	}
}

void Player::ChangeState(StateCode _NextState)
{
	State = _NextState;
}

void Player::AnimationControl()
{
	float time = 1.0f / 60.0f;
	switch (State)
	{
	case StateWaiting:
		PlayAnimation(AnimationCode::AnimationWaiting, 0.1f);
		break;
	case StateWalk:
		PlayAnimation(AnimationCode::AnimationWalk, 0.1f);
		break;
	case StateRun:
		PlayAnimation(AnimationCode::AnimationRun, 0.1f);
		time = 1.0f / 60;
		break;
	case StateAttack:
		PlayAnimation(AnimationCode::AnimationAttack, 0.1f);
		break;
	case StateDamage:
		PlayAnimation(AnimationCode::AnimationHit, 0.1f);
		break;
	case StateDead:
		PlayAnimation(AnimationCode::AnimationDead, 0.1f);
	default:
		break;
	}
	Animation.Update(time);
}

void Player::PlayAnimation(AnimationCode _AnimCode, float interpolateTime)
{
	if (Animation.GetNowAnimationNo() != _AnimCode)
	{
		Animation.PlayAnimation(_AnimCode, interpolateTime);
	}
}
