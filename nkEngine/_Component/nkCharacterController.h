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
	class CharacterController : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		CharacterController()
		{
		}

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
		void Init(float radius, float height, const Vector3& pos);

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
		const Vector3& GetPosition() const
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
		void SetPosition(const Vector3& pos)
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
		const Vector3& GetMoveSpeed() const
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
		void SetMoveSpeed(const Vector3& ms)
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
		 * @param gravity �d�͒l.
		 */
		void SetGravity(float gravity)
		{
			Gravity_ = gravity;
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
		Vector3 Position_ = Vector3::Zero; 
		/** �ړ����x. */
		Vector3 MoveSpeed_ = Vector3::Zero;
		/** �W�����v�t���O. */
		bool isJump_ = false;
		/** �n�ʂ̏�ɂ���Btrue:�n�ʏ�,false:��. */
		bool isOnGround_ = true;
		/** �J�v�Z���`��̃R���C�_�[. */
		CapsuleCollider Collider_;
		/** ���a. */
		float Radius_ = 0.0f;
		/** ����. */
		float Height_ = 0.0f;
		/** ����. */
		RigidBody RigidBody_;
		/** �d��. */
		float Gravity_ = -9.8f;

	};

}// namespace nkEngine