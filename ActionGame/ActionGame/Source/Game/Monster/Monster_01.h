#pragma once

#include"IMonster.h"

class Monster_01 : public IMonster
{
public:
	enum AnimationCode
	{
		AnimationInvalid = -1,
		AnimationWaiting = 0,
		AnimationWalk,
		AnimationRun,
		AnimationAttack_01,
		AnimationAttack_02,
		AnimationHit,
		AnimationDeath,
		AnimationNum,
	};
public:
	Monster_01();
	~Monster_01();
	void Init()override;
	void Update()override;
	void Render()override;
	void Release()override;
	void Damage()override;

	//�A�j���[�V������ύX����
	void PlayAnimation(AnimationCode _AnimCode, float interpolateTime)
	{
		if (Animation.GetNowAnimationNo() != _AnimCode)
		{
			Animation.PlayAnimation(_AnimCode, interpolateTime);
		}
	}
	//���݂̃A�j���[�V�����Ɋ֌W�Ȃ��ݒ肷��
	void PlayAnimationAbs(AnimationCode _AnimCode, float interpolateTime)
	{
		Animation.PlayAnimation(_AnimCode, interpolateTime);
	}

	void AnimationControl()override;
private:
	std::unique_ptr<btCollisionObject>	collisionObject;		//�R���W�����I�u�W�F�N�g�B
	std::unique_ptr<CSphereCollider>	sphereShape;			//����

};