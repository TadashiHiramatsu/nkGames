/**
 * @file _Graphics\nkCamera.h
 *
 * �J�����N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �J�����N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Camera : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Camera()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Camera()
		{
		}

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();

		/**
		 * ����].
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot ��]��(�x).
		 */
		void SpinHorizontally(float rot);

		/**
		 * �c��].
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot ��]��(�x).
		 */
		void SpinVertically(float rot);

		/**
		 * �r���[�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The view matrix.
		 */
		const Matrix& GetViewMatrix() const
		{
			return ViewMatrix_;
		}

		/**
		 * �r���[�s��̋t�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The view inverse matrix.
		 */
		const Matrix& GetViewInvMatrix() const
		{
			return ViewInvMatrix_;
		}

		/**
		 * �v���W�F�N�V�����s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The projection matrix.
		 */
		const Matrix& GetProjectionMatrix() const
		{
			return ProjMatrix_;
		}

		/**
		 * ��]�s��̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The rotation matrix.
		 */
		const Matrix& GetRotationMatrix() const
		{
			return RotationMatrix_;
		}

		/**
		 * ��]�s��̋t�s��擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The rotation inverse matrix.
		 */
		const Matrix& GetRotationInvMatrix() const
		{
			return RotationInvMatrix_;
		}

		/**
		 * �J�����̎��_�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The position.
		 */
		const Vector3& GetPosition() const
		{
			return Position_;
		}

		/**
		 * �J�����̎��_�̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param pos ���_�x�N�g��.
		 */
		void SetPosition(const Vector3& pos)
		{
			Position_ = pos;
		}

		/**
		 * �J�����̎��_�����x�N�g���̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The position direction.
		 */
		const Vector3& GetPosDirection() const
		{
			return PosDirection_;
		}

		/**
		 * �J�����̎��_�����x�N�g���̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dir ���_�x�N�g��.
		 */
		void SetPosDirection(const Vector3& dir)
		{
			PosDirection_ = dir;
		}

		/**
		 * �J�����̒����_�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The target.
		 */
		const Vector3& GetTarget() const
		{
			return Target_;
		}

		/**
		 * �J�����̒����_�̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param target �����_�x�N�g��.
		 */
		void SetTarget(const Vector3& target)
		{
			Target_ = target;
		}

		/**
		 * �J�����̏�����̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The up.
		 */
		const Vector3& GetUp() const
		{
			return Up_;
		}

		/**
		 * �J�����̏�����̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param up ������x�N�g��.
		 */
		void SetUp(const Vector3& up)
		{
			Up_ = up;
		}

		/**
		 * �J�����̎��_�A�����_�Ԃ̋������擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The distance.
		 */
		const float GetDistance() const
		{
			return Distance_;
		}

		/**
		 * �J�����̎��_�A�����_�Ԃ̋�����ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param distance ����.
		 */
		void SetDistance(float distance)
		{
			Distance_ = distance;
		}

		/**
		 * �J�����̉�p���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The Angle_.
		 */
		float GetAngle() const
		{
			return Angle_;
		}

		/**
		 * �J�����̉�p��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param angle ��p.
		 */
		void SetAngle(float angle)
		{
			Angle_ = angle;
		}

		/**
		 * �J�����̃A�X�y�N�g����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The aspect.
		 */
		float GetAspect() const
		{
			return Aspect_;
		}

		/**
		 * �J�����̃A�X�y�N�g���ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param aspect �A�X�y�N�g��.
		 */
		void SetAspect(float aspect)
		{
			Aspect_ = aspect;
		}

		/**
		 * �J�����̃j�A���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The near.
		 */
		float GetNear() const
		{
			return Near_;
		}

		/**
		 * �J�����̃j�A��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param fnear �j�A.
		 */
		void SetNear(float fnear)
		{
			Near_ = fnear;
		}

		/**
		 * �J�����̃t�@�[���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The far.
		 */
		float GetFar() const
		{
			return Far_;
		}

		/**
		 * �J�����̃t�@�[��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param ffar �t�@�[.
		 */
		void SetFar(float ffar)
		{
			Far_ = ffar;
		}

	private:

		/** �r���[�s��. */
		Matrix ViewMatrix_ = Matrix::Identity;
		/** �r���[�s��̋t�s��. */
		Matrix ViewInvMatrix_ = Matrix::Identity;
		/** �v���W�F�N�V�����s��. */
		Matrix ProjMatrix_ = Matrix::Identity;
		/** ��]�s��. */
		Matrix RotationMatrix_ = Matrix::Identity;
		/** ��]�s��̋t�s��. */
		Matrix RotationInvMatrix_ = Matrix::Identity;

		/** �J�����̎��_. */
		Vector3 Position_ = Vector3::Zero;
		/** �J�����̒����_. */
		Vector3 Target_ = Vector3::Zero;
		/** �J�����̏����. */
		Vector3 Up_ = Vector3::Up;

		/** �|�W�V�����̕����x�N�g��. */
		Vector3 PosDirection_ = Vector3::Zero;
		/** ����. */
		float Distance_ = 0;

		/** ��p. */
		float Angle_ = D3DXToRadian(45);
		/** �A�X�y�N�g��. */
		float Aspect_ = 0.0f;
		/** �j�A. */
		float Near_ = 0.1f;
		/** �t�@�[. */
		float Far_ = 1200.0f;

		/** ����. */
		float LowerLimit_ = -0.7f;
		/** ���. */
		float UpperLimit_ = 0.7f;

	};

}// namespace nkEngine