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
		int Level;					//レベル
		int Experience;				//現在の経験値
		int NextLevelExperience;	//次のレベルへの経験値
		int	Attack;					//攻撃力
		int MaxHp; //体力
		int NowHp; //体力
		int HitTime; //無敵時間
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

	//経験値加算
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

	//状態。
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

	float LocalTime = 0; //無敵時間計測用
	float itime; //ライフ回復時間用

	std::unique_ptr<btCollisionObject>	collisionObject;		//コリジョンオブジェクト。
	std::unique_ptr<CSphereCollider>	sphereShape;
};