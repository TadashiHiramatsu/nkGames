/**
 * @file	_Physics\nkRigidBody.h
 *
 * ���̃N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"
#include"../_Math/nkVector.h"

namespace nkEngine
{

	/**
	 * ���̏��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	struct RigidBodyInfoS : Noncopyable
	{
	public:

		/** ���W. */
		Vector3 Position_ = Vector3::Zero;
		/** ��]. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** �R���C�_�[. */
		ICollider* Collider_ = nullptr;
		/** ����. */
		float Mass_ = 0.0f;

	};

	/**
	 * ���̃N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class RigidBody : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		RigidBody()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~RigidBody()
		{
			Release();
		}

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
		btRigidBody* RigidBody_ = nullptr;
		/** ���[�V�����X�e�[�g. */
		btDefaultMotionState* MotionState_ = nullptr;
	
	};

}// namespace nkEngine