/**
 * @file _Component\nkTransform.h
 *
 * �g�����X�t�H�[���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �g�����X�t�H�[���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class Transform : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Transform()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Transform()
		{
		}

		/**
		 * ���[���h�s��Ȃǂ̍X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * �r���{�[�h����X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void BillboardUpdate(const Matrix& rot);
	
	public:

		/** �e�q�֌W�����e��Transform�N���X�̃|�C���^. */
		Transform* Parent_ = nullptr;
		/** �e�ɂ���s��. */
		Matrix* ParentMatrix_ = nullptr;

		/** �ʒu�x�N�g��. */
		Vector3 Position_ = Vector3::Zero;
		/** �g��x�N�g��. */
		Vector3 Scale_ = Vector3::One;
		/** ��]�x�N�g��. */
		Quaternion Rotation_ = Quaternion::Identity;

		/** ���[�J���̃��[���h�s��. */
		Matrix LocalMatrix_ = Matrix::Identity;
		/** ���[���h�s��. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ���[���h�s��̋t�s��. */
		Matrix WorldInvMatrix_ = Matrix::Identity;
		/** ��]�s��. */
		Matrix RotationMatrix_ = Matrix::Identity;

	};

}// namespace nkEngine