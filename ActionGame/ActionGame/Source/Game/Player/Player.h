#pragma once

#include "nkEngine/_Physics/nkCapsuleCollider.h"
#include "nkEngine/_Physics/CRigidBody.h"

class Player : public CGameObject
{
public:
	enum AnimationCode
	{
		AnimationWaiting = 0,
		AnimationRun,
		AnimationNum,
	};
	enum StateCode
	{
		StateWaiting = 0,
		StateRun,
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

	StateCode					state;				//状態。
	StateCode					lastFrameState;		//前のフレームの状態。

	CRigidBody RigidBody;
	CCapsuleCollider CapsuleCollider;

	float m_height;
	float m_radius;
	bool m_isOnGround = true;
};