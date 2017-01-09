/**
 * @file	_Physics\nkRigidBody.h
 *
 * ���̃N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ���̏��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct RigidBodyInfoS
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		RigidBodyInfoS() :
			Collider_(nullptr),
			Mass_(0.0f),
			Position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			Rotation_(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
		{
		}

	public:

		/** ���W. */
		D3DXVECTOR3 Position_;
		/** ��]. */
		D3DXQUATERNION Rotation_;
		/** �R���C�_�[. */
		ICollider* Collider_;
		/** ����. */
		float Mass_;

	};

	/**
	 * ���̃N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CRigidBody
	{
	public:

		/**
		 * Default constructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CRigidBody();

		/**
		 * Destructor.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CRigidBody();

		/**
		 * �쐬.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rbInfo	Information describing the rb.
		 */
		void Create(RigidBodyInfoS& rbInfo);

		/**
		 * ���.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();

		/**
		 * Gets the body.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the body.
		 */
		btRigidBody* GetBody()
		{
			return RigidBody_;
		}

	private:
		/** ����. */
		btRigidBody* RigidBody_;
		/** ���[�V�����X�e�[�g. */
		btDefaultMotionState* MotionState_;
	};

}// namespace nkEngine