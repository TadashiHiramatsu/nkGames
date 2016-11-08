#pragma once

#include"nkEngine/_Component/nkCharacterController.h"
#include"nkEngine/_Graphics/Particle/nkParticleEmitter.h"
#include"..\AnimationEvent\AnimationEventController.h"

class Player : public CGameObject
{
public:
	enum AnimationCode
	{
		AnimationInvalid = -1,
		AnimationWaiting = 0,
		AnimationRun,
		AnimationAttack,
		AnimationNum,
	};
	enum StateCode
	{
		StateWaiting = 0,
		StateRun,
		StateAttack,
		StateJump,
	};
public:
	Player();
	~Player();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;


	D3DXVECTOR3& GetPos()
	{
		return Transform.Position;
	}

private:

	void ChangeState(StateCode _NextState);
	void AnimationControl();
	void PlayAnimation(AnimationCode _AnimCode, float interpolateTime);
private:
	CTransform Transform;
	CLight Light;
	CModelRender Model;
	CAnimation Animation;

	//èÛë‘ÅB
	StateCode State;			

	CharacterController CharacterController;

	CParticleEmitter Particle;
	D3DXMATRIX* mParticle;
	D3DXVECTOR3 ParticlePos;
};