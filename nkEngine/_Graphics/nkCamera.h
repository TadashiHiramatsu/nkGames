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
	class Camera
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Camera();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Camera();

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
		 * @param rot ��]�ʁB���W�A��.
		 */
		void SpinHorizontally(float rot);

		/**
		 * �c��].
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param rot ��]�ʁB���W�A��.
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
		const D3DXMATRIX& GetViewMatrix()
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
		const D3DXMATRIX& GetViewInvMatrix()
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
		const D3DXMATRIX& GetProjectionMatrix()
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
		const D3DXMATRIX& GetRotationMatrix()
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
		const D3DXMATRIX& GetRotationInvMatrix()
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
		const D3DXVECTOR3& GetPosition()
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
		void SetPosition(const D3DXVECTOR3& pos)
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
		const D3DXVECTOR3& GetPosDirection()
		{
			return PosDirection_;
		}

		/**
		 * �J�����̎��_�����x�N�g���̐ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param _dir ���_�x�N�g��.
		 */
		void SetPosDirection(const D3DXVECTOR3& _dir)
		{
			PosDirection_ = _dir;
		}

		/**
		 * �J�����̒����_�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The target.
		 */
		const D3DXVECTOR3& GetTarget()
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
		void SetTarget(const D3DXVECTOR3& target)
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
		const D3DXVECTOR3& GetUp()
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
		void SetUp(const D3DXVECTOR3& up)
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
		const float GetDistance()
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
		void SetDistance(const float distance)
		{
			Distance_ = distance;
		}

		/**
		 * �J�����̉�p���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The fovy.
		 */
		const float GetFovy()
		{
			return Fovy_;
		}

		/**
		 * �J�����̉�p��ݒ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param fovy ��p.
		 */
		void SetFovy(const float fovy)
		{
			Fovy_ = fovy;
		}

		/**
		 * �J�����̃A�X�y�N�g����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The aspect.
		 */
		const float GetAspect()
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
		void SetAspect(const float aspect)
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
		const float GetNear()
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
		void SetNear(const float fnear)
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
		const float GetFar()
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
		void SetFar(const float ffar)
		{
			Far_ = ffar;
		}

	private:

		/** �r���[�s��. */
		D3DXMATRIX ViewMatrix_;
		/** �r���[�s��̋t�s��. */
		D3DXMATRIX ViewInvMatrix_;
		/** �v���W�F�N�V�����s��. */
		D3DXMATRIX ProjMatrix_;
		/** ��]�s��. */
		D3DXMATRIX RotationMatrix_;
		/** ��]�s��̋t�s��. */
		D3DXMATRIX RotationInvMatrix_;

		/** �J�����̎��_. */
		D3DXVECTOR3 Position_;
		/** �J�����̒����_. */
		D3DXVECTOR3 Target_;
		/** �J�����̏����. */
		D3DXVECTOR3 Up_;

		/** �|�W�V�����̕����x�N�g��. */
		D3DXVECTOR3 PosDirection_;
		/** ����. */
		float Distance_;

		/** ��p. */
		float Fovy_;
		/** �A�X�y�N�g��. */
		float Aspect_;
		/** �j�A. */
		float Near_;
		/** �t�@�[. */
		float Far_;

		/** ����. */
		float LowerLimit_;
		/** ���. */
		float UpperLimit_;

	};

}// namespace nkEngine