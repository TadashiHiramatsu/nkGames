#include"stdafx.h"
#include"Monster_01.h"

Monster_01::Monster_01()
{

}

Monster_01::~Monster_01()
{
}

void Monster_01::Init()
{
	Model.Load("Monster_01.X", &Animation);
	IMonster::Init();
	Model.SetRimLight(true);

	Transform.Position = DefaultPosition = D3DXVECTOR3(1, 1, 0);
	
	ChangeState(StateCode::StateWaiting);
	PlayAnimation(AnimationWaiting,0.3f);
	Animation.SetAnimationLoopFlags(AnimationAttack_01, false);

	m_CharacterController.Init(0.4f, 0.3f, Transform.Position);
}

void Monster_01::Update()
{

	switch (State)
	{
	case StateWaiting:
	{
		if (GetToPlayerDis() <= toPlayerMaxDis)
		{
			ChangeState(StateCode::StateChase);
			break;
		}
		MoveDir *= 0.8f;
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
		MoveDir = D3DXVECTOR3(toD.x, 0, toD.y);
		D3DXQuaternionRotationAxis(&Transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(MoveDir.x, MoveDir.z) + D3DXToRadian(180.0f));
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
		MoveDir = D3DXVECTOR3(toP.x, 0, toP.y);
		D3DXQuaternionRotationAxis(&Transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(MoveDir.x, MoveDir.z) + D3DXToRadian(180.0f));
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
		MoveDir = D3DXVECTOR3(0, 0, 0);
	}
	break;
	default:
		break;
	}

	m_CharacterController.SetMoveSpeed(MoveDir);
	m_CharacterController.Update();
	Transform.Position = m_CharacterController.GetPosition();

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