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
	class Transform
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		Transform();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~Transform();

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
		void BillboardUpdate(const D3DXMATRIX& rot);
	
	public:

		/** �e�q�֌W�����e��Transform�N���X�̃|�C���^. */
		Transform* Parent_;
		/** �e�ɂ���s��. */
		D3DXMATRIX* ParentMatrix_;

		/** �ʒu�x�N�g��. */
		D3DXVECTOR3 Position_;
		/** �g��x�N�g��. */
		D3DXVECTOR3 Scale_;
		/** ��]�x�N�g��. */
		D3DXQUATERNION Rotation_;

		/** ���[�J���̃��[���h�s��. */
		D3DXMATRIX LocalMatrix_;
		/** ���[���h�s��. */
		D3DXMATRIX WorldMatrix_;
		/** ���[���h�s��̋t�s��. */
		D3DXMATRIX WorldInvMatrix_;
		/** ��]�s��. */
		D3DXMATRIX RotationMatrix_;

	};

}// namespace nkEngine