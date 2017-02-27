/**
 * @file _Component\nkCharacterController.h
 *
 * �L�����N�^�[�R���g���[���N���X�̒�`.
 */
#pragma once

#include"../_Physics/nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	 * �L�����N�^�[�R���g���[���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class CharacterController
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		CharacterController();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~CharacterController()
		{
		}

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param radius The radius.
		 * @param height The height.
		 * @param pos    The position.
		 */
		void Init(float radius, float height, const D3DXVECTOR3& pos);

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * ���W���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The position.
		 */
		const D3DXVECTOR3& GetPosition() const 
		{
			return Position_;
		}

		/**
		 * ���W��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param pos The position.
		 */
		void SetPosition(const D3DXVECTOR3& pos)
		{
			Position_ = pos;
		}

		/**
		 * �ړ����x���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The move speed.
		 */
		const D3DXVECTOR3& GetMoveSpeed() const
		{
			return MoveSpeed_;
		}

		/**
		 * �ړ����x��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param ms The milliseconds.
		 */
		void SetMoveSpeed(const D3DXVECTOR3& ms)
		{
			MoveSpeed_ = ms;
		}

		/**
		 * �W�����v������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Jump()
		{
			isJump_ = true;
			isOnGround_ = false;
		}

		/**
		 * �W�����v�t���O���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if jump, false if not.
		 */
		bool IsJump() const
		{
			return isJump_;
		}

		/**
		 * �n�ʂ̏�ɂ��邩����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return True if on ground, false if not.
		 */
		bool IsOnGround() const
		{
			return isOnGround_;
		}

		/**
		 * �R���C�_�[���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the collider.
		 */
		CapsuleCollider* GetCollider()
		{
			return &Collider_;
		}

		/**
		 * �d�͂�ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param _gravity The gravity.
		 */
		void SetGravity(float _gravity)
		{
			Gravity_ = _gravity;
		}

		/**
		 * ���̂��擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return Null if it fails, else the rigidbody.
		 */
		RigidBody* GetRigidbody()
		{
			return &RigidBody_;
		}

		/**
		 * ���̂𕨗��G���W������폜.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void RemoveRigidBody();

	private:

		/** ���W. */
		D3DXVECTOR3 Position_; 
		/** �ړ����x. */
		D3DXVECTOR3 MoveSpeed_;
		/** �W�����v�t���O. */
		bool isJump_;
		/** �n�ʂ̏�ɂ���Btrue:�n�ʏ�,false:��. */
		bool isOnGround_;
		/** �J�v�Z���`��̃R���C�_�[. */
		CapsuleCollider Collider_;
		/** ���a. */
		float Radius_;
		/** ����. */
		float Height_;
		/** ����. */
		RigidBody RigidBody_;
		/** �d��. */
		float Gravity_;

	};

}// namespace nkEngine