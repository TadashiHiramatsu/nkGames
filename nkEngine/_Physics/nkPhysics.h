/**
 * @file	_Physics\nkPhysics.h
 *
 * �������[���h�N���X�̒�`.
 */
#pragma once

#include"nkRigidBody.h"

namespace nkEngine
{

	/**
	 * �������[���h�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CPhysics : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CPhysics()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CPhysics()
		{
			Release();
		}

		/**
		 * ������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Init();

		/**
		 * �X�V.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Update();

		/**
		 * �J��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();

		/**
		 * �_�C�i�~�b�N���[���h�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	Null if it fails, else the dynamic world.
		 */
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return DynamicWorld_;
		}

		/**
		 * ���̂̒ǉ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rb	����.
		 */
		void AddRigidBody(RigidBody* rb);

		/**
		 * ���̂̍폜.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rb	����.
		 */
		void RemoveRigidBody(RigidBody* rb);

		/**
		 * �ʖʈ�|�H.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param 		  	castShape			 	The cast shape.
		 * @param 		  	convexFromWorld		 	The convex from world.
		 * @param 		  	convexToWorld		 	The convex to world.
		 * @param [in,out]	resultCallback		 	The result callback.
		 * @param 		  	allowedCcdPenetration	(Optional) The allowed CCD penetration.
		 */
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			DynamicWorld_->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}

	private:

		/** �Փ˔���z�u. */
		btDefaultCollisionConfiguration* CollisionConfiguration_ = nullptr;
		/** �Փˉ�������. */
		btCollisionDispatcher* CollisionDispatcher_ = nullptr;
		/** �u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�. */
		btBroadphaseInterface* OverlappingPairCache_ = nullptr;
		/** �R���X�g���C���g�\���o�[�B�S�������̉�������. */
		btSequentialImpulseConstraintSolver* ConstraintSolver_ = nullptr;
		/** ���[���h. */
		btDiscreteDynamicsWorld* DynamicWorld_ = nullptr;

	};

}// namespace nkEngine