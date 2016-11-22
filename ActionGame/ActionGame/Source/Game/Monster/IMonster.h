#pragma once

#include"..\AnimationEvent\AnimationEventController.h"
#include"..\AnimationEvent\CollisionWorld.h"

#include"nkEngine/_Component/nkCharacterController.h"
#include"..\Player\Player.h"
#include"..\Item\DropItem.h"


class IMonster : public CGameObject
{
public:
	enum StateCode
	{
		StateSpawn, //�o��
		StateWaiting, //�����~�܂�
		StateLoitering, //�p�j
		StateChase, //�ǂ�����
		StateAttack, //�U��
		StateDamage, //�_���[�W
		StateDead, //�����Ď�
	};

public:
	IMonster();
	virtual ~IMonster();
	virtual void Init()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

	virtual void Damage(){}

protected:

	//State��ύX����
	//param[in] �ύX���StateCode
	void ChangeState(StateCode _NextState)
	{
		State = _NextState;
	}

	//�A�j���[�V�����Ǘ�
	virtual void AnimationControl() {}

	//�v���C���[�ւ̕����x�N�g�����v�Z
	D3DXVECTOR2& GetToPlayerDir()
	{
		D3DXVECTOR2 toP = D3DXVECTOR2(pPlayerPos->x,pPlayerPos->z) - D3DXVECTOR2(Transform.Position.x, Transform.Position.z);
		D3DXVec2Normalize(&toP, &toP);
		return toP;
	}

	//�v���C���[�Ƃ̋������v�Z
	//�������l�����Ȃ�������Ԃ��܂�
	float GetToPlayerDis()
	{
		D3DXVECTOR3 toP = *pPlayerPos - Transform.Position;
		return D3DXVec2Length(&D3DXVECTOR2(toP.x, toP.z));
	}


	//�ړI�n�܂ł̕����x�N�g�����擾
	D3DXVECTOR2& GetToDestination()
	{
		D3DXVECTOR2 toD = Destination - D3DXVECTOR2(Transform.Position.x, Transform.Position.z);
		D3DXVec2Normalize(&toD, &toD);
		return toD;
	}

	//�ړI�n�܂ł̋������v�Z
	//�������l�����Ȃ�������Ԃ��܂�
	float GetToDestinationDis()
	{
		D3DXVECTOR2 toD = Destination - D3DXVECTOR2(Transform.Position.x, Transform.Position.z);
		return D3DXVec2Length(&toD);
	}

protected:
	CModelRender Model;
	CTransform Transform;
	CLight Light;
	CAnimation Animation;

	float Radius;
	float Height;

	int Hp;

	//�X�|�[���ʒu
	//��������̋����ړ��ł���
	D3DXVECTOR3 DefaultPosition;
	float Distance; //����
	D3DXVECTOR2 Destination; //�ړI�n

	//�v���C���[��ǂ�������ő勗��
	//�����鋗�������p
	float toPlayerMaxDis; 

	D3DXVECTOR3* pPlayerPos;//�v���C���[�̃|�W�V�����̃A�h���X
	float PlayerAttackDis;

	float WaitingTime; //�����~�܂鎞��
	float LocalTime; //���[�J���^�C��

	StateCode State;
	CharacterController m_CharacterController;

	AnimationEventController animEvent;
};