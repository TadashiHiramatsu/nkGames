#pragma once

#include "nkEngine/_Physics/nkCapsuleCollider.h"
#include "nkEngine/_Physics/CRigidBody.h"

namespace nkEngine
{
	class CharacterController
	{
	public:
		//�R���X�g���N�^
		CharacterController();

		//�f�X�g���N�^
		~CharacterController();

		//������
		void Init(float _radius,float _height,const D3DXVECTOR3& _pos);

		//�X�V
		void Update();

		//���W���擾
		const D3DXVECTOR3& GetPosition() const 
		{
			return Position;
		}

		//���W��ݒ�
		void SetPosition(const D3DXVECTOR3& _pos)
		{
			Position = _pos;
		}

		//�ړ����x���擾
		const D3DXVECTOR3& GetMoveSpeed()const
		{
			return MoveSpeed;
		}

		//�ړ����x��ݒ�
		void SetMoveSpeed(const D3DXVECTOR3& _ms)
		{
			MoveSpeed = _ms;
		}

		//�W�����v������
		void Jump()
		{
			isJump = true;
			isOnGround = false;
		}

		//�W�����v�t���O���擾
		bool IsJump()const
		{
			return isJump;
		}

		//�n�ʂ̏�ɂ��邩����
		bool IsOnGround()const
		{
			return isOnGround;
		}

		//�R���C�_�[���擾
		CCapsuleCollider* GetCollider()
		{
			return &Collider;
		}

		//�d�͂�ݒ�
		void SetGravity(float _gravity)
		{
			Gravity = _gravity;
		}

		//���̂��擾
		CRigidBody* GetRigidbody()
		{
			return &RigidBody;
		}

		//���̂𕨗��G���W������폜
		void RemoveRigidBody();

	private:
		//���W
		D3DXVECTOR3 Position; 
		//�ړ����x
		D3DXVECTOR3 MoveSpeed; 
		//�W�����v�t���O
		bool isJump;
		//�n�ʂ̏�ɂ���
		bool isOnGround;
		//�R���C�_�[
		CCapsuleCollider Collider;
		//���a
		float Radius;
		//����
		float Height;
		//����
		CRigidBody RigidBody;
		//�d��
		float Gravity;
	};
}