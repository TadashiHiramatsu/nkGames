#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

class Player : public IGameObject
{
public:
	struct PlayerParameter
	{
		PlayerParameter()
		{
			Level = 1;
			Experience = 0;
			NextLevelExperience = 10;
			Attack = 1;
			MaxHp = NowHp = 100;
			HitTime = 1.0f;
		}
		int Level;					//���x��
		int Experience;				//���݂̌o���l
		int NextLevelExperience;	//���̃��x���ւ̌o���l
		int	Attack;					//�U����
		int MaxHp; //�̗�
		int NowHp; //�̗�
		int HitTime; //���G����
	};

	enum AnimationCode
	{
		AnimationInvalid = -1,
		AnimationWaiting = 0,
		AnimationWalk,
		AnimationRun,
		AnimationAttack,
		AnimationHit,
		AnimationDead,
		AnimationNum,
	};
	enum StateCode
	{
		StateWaiting = 0,
		StateWalk,
		StateRun,
		StateAttack,
		StateDamage,
		StateDead,
	};
public:
	Player();
	~Player();
	void Start()override;
	void Update()override;
	void Render()override;
	void Release()override;

	void Damage();

	void ParameterUpdate();

	//�o���l���Z
	void AddExperience(int _Add)
	{
		PP.Experience += _Add;
	}

	PlayerParameter& GetPlayerParameter()
	{
		return PP;
	}

	D3DXVECTOR3& GetPos()
	{
		return transform.Position;
	}

private:
	void ChangeState(StateCode _NextState);
	void AnimationControl();
	void PlayAnimation(AnimationCode _AnimCode, float interpolateTime);
private:
	CLight Light;
	CModelRender Model;
	CAnimation Animation;

	//��ԁB
	StateCode State;			


	float Radius;
	float Height;
	CharacterController CharacterController;
	AnimationEventController animEvent;

	PlayerParameter PP;

	CParticleEmitter Particle;
	D3DXMATRIX* mParticle;
	D3DXVECTOR3 ParticlePos;

	Transform LWeaponTransform;
	CLight LWeaponLight;
	CModelRender LWeaponModel;
	Transform RWeaponTransform;
	CLight RWeaponLight;
	CModelRender RWeaponModel;

	float LocalTime = 0; //���G���Ԍv���p
	float itime; //���C�t�񕜎��ԗp

	std::unique_ptr<btCollisionObject>	collisionObject;		//�R���W�����I�u�W�F�N�g�B
	std::unique_ptr<CSphereCollider>	sphereShape;
};