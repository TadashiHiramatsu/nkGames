#include"stdafx.h"
#include"Monster_01.h"

#include"..\GameScene.h"

namespace
{
	AnimationEventGroup AnimationEventTbl[Monster_01::AnimationNum]
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
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.0f, 1.0f, 1.0f, 2, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.1f, 1.0f, 1.0f, 2, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.2f, 1.0f, 1.0f, 2, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.3f, 1.0f, 1.0f, 2, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
			EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(0.4f, 1.0f, 1.0f, 2, "Joint_3_3", D3DXVECTOR3(0,0,0), 0),
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
}

Monster_01::Monster_01()
{

}

Monster_01::~Monster_01()
{
}

void Monster_01::Start()
{
	SMDResources().Load(SkinModelData, "Monster_01.X", &Animation);

	Model.Load(SkinModelData.GetBody());

	IMonster::Start();
	Model.SetRimLight(true);

	pPlayerPos = &g_Player->GetPos();
	
	ChangeState(StateCode::StateWaiting);
	PlayAnimation(AnimationWaiting,0.3f);
	Animation.SetAnimationLoopFlags(AnimationAttack_01, false);
	Animation.SetAnimationLoopFlags(AnimationHit, false);
	Animation.SetAnimationLoopFlags(AnimationDeath, false);

	m_CharacterController.Init(Radius, Height, transform.Position);
	
	animEvent.Init(&Model, &Animation, AnimationEventTbl, sizeof(AnimationEventTbl) / sizeof(AnimationEventTbl[0]));

	sphereShape.reset(new CSphereCollider);
	sphereShape->Create(Radius);
	collisionObject.reset(new btCollisionObject());
	collisionObject->setCollisionShape(sphereShape->GetBody());
}

void Monster_01::Update()
{
	D3DXVECTOR3 MoveSpeed = m_CharacterController.GetMoveSpeed();
	switch (State)
	{
	case StateWaiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis)
		{
			ChangeState(StateCode::StateChase);
			break;
		}
		MoveSpeed *= 0.8f;
		if (LocalTime >= WaitingTime)
		{
			ChangeState(StateCode::StateLoitering);
			Destination = D3DXVECTOR2((Random().GetRandDouble() - 0.5f)*Distance, (Random().GetRandDouble() - 0.5f)*Distance) + D3DXVECTOR2(DefaultPosition.x, DefaultPosition.z);
			LocalTime = 0;
			break;
		}
		LocalTime += Time().DeltaTime();
	}
	break;
	case StateLoitering:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis)
		{
			ChangeState(StateCode::StateChase);
			break;
		}
		if (GetToDestinationDis() <= 0.2)
		{
			ChangeState(StateCode::StateWaiting);
			break;
		}
		D3DXVECTOR2 toD = GetToDestination();
		MoveSpeed = D3DXVECTOR3(toD.x, 0, toD.y);
		D3DXQuaternionRotationAxis(&transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	}
	break;
	case StateChase:
	{
		if (GetToPlayerDis() >= toPlayerMaxDis)
		{
			ChangeState(StateCode::StateWaiting);
			break;
		}
		if (GetToPlayerDis() <= PlayerAttackDis)
		{
			ChangeState(StateCode::StateAttack);
			break;
		}
		D3DXVECTOR2 toP = GetToPlayerDir();
		MoveSpeed = D3DXVECTOR3(toP.x, 0, toP.y);
		D3DXQuaternionRotationAxis(&transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(MoveSpeed.x, MoveSpeed.z) + D3DXToRadian(180.0f));
	}
	break;
	case StateAttack:
	{
		if (!Animation.IsPlayAnim())
		{
			if (GetToPlayerDis() > PlayerAttackDis)
			{
				ChangeState(StateCode::StateChase);
				break;
			}
			else
			{
				PlayAnimationAbs(AnimationAttack_01, 0.3f);
			}
		}
		MoveSpeed = D3DXVECTOR3(0, 0, 0);
	}
	break;
	case StateDamage:
	{
		if (!Animation.IsPlayAnim())
		{
			ChangeState(StateChase);
			break;
		}
		MoveSpeed = D3DXVECTOR3(0, 0, 0);
	}
	break;
	case StateDead:
	{
		if (!Animation.IsPlayAnim())
		{
			isActive = false;
			break;
		}
		MoveSpeed = D3DXVECTOR3(0, 0, 0);
	}
	break;
	default:
		break;
	}

	m_CharacterController.SetMoveSpeed(MoveSpeed);
	m_CharacterController.Update();
	transform.Position = m_CharacterController.GetPosition();

	animEvent.Update();

	Damage();

	AnimationControl();
	IMonster::Update();
}

void Monster_01::AnimationControl()
{
	float AnimationTime = 1.0f / 60.0f;
	switch (State)
	{
	case StateWaiting:
		PlayAnimation(AnimationWaiting, 0.3f);
		break;
	case StateLoitering:
		PlayAnimation(AnimationWalk, 0.3f);
		break;
	case StateChase:
		PlayAnimation(AnimationRun, 0.3f);
		break;
	case StateAttack:
		PlayAnimation(AnimationAttack_01, 0.3f);
		break;
	case StateDamage:
		PlayAnimation(AnimationHit, 0.3f);
		break;
	case StateDead:
		PlayAnimation(AnimationDeath, 0.3f);
		break;
	default:
		break;
	}
	Animation.Update(AnimationTime);
}

void Monster_01::Render()
{
	IMonster::Render();
}

void Monster_01::Release()
{
	IMonster::Release();
}

void Monster_01::Damage()
{
	if (State == StateDead) {
		//死んでる。
		return;
	}

	float offset = Radius + Height * 0.5f;
	D3DXVECTOR3 centerPos;
	centerPos = transform.Position;
	centerPos.y += offset;

	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
	collisionObject->setWorldTransform(trans);

	//当たっているコリジョンを検出
	const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
		CollisionWorld::enDamageToEnemy,
		collisionObject.get()
	);

	if (!dmgCol) {
		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		collisionObject->setWorldTransform(trans);
		const CollisionWorld::Collision* dmgCol = g_CollisionWorld->FindOverlappedDamageCollision(
			CollisionWorld::enDamageToEnemy,
			collisionObject.get()
		);
	}
	if (dmgCol != NULL && State != StateDamage) {
		//ダメージを食らっている。
		Hp -= dmgCol->Damage;
		if (Hp <= 0) {
			//死亡。
			ChangeState(StateDead);
			g_Player->AddExperience(10);

			DropItem* DI = NewGO<DropItem>();
			DI->SetTransform(transform);
		}
		else 
		{
			ChangeState(StateDamage);
		}
	}
}
