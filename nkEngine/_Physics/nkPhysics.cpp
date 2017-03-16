/**
 * @file	_Physics\nkPhysics.cpp
 *
 * �������[���h�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPhysics.h"

namespace nkEngine
{

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CPhysics::Init()
	{
		//�����G���W�����������B
		CollisionConfiguration_ = new btDefaultCollisionConfiguration();

		CollisionDispatcher_ = new	btCollisionDispatcher(CollisionConfiguration_);

		OverlappingPairCache_ = new btDbvtBroadphase();

		ConstraintSolver_ = new btSequentialImpulseConstraintSolver;

		DynamicWorld_ = new btDiscreteDynamicsWorld(
			CollisionDispatcher_,
			OverlappingPairCache_,
			ConstraintSolver_,
			CollisionConfiguration_
		);

		//�d�͌v�Z
		DynamicWorld_->setGravity(btVector3(0, -10, 0));
	}

	/**
	 * �X�V.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CPhysics::Update()
	{
		DynamicWorld_->stepSimulation(GAME_DELTA_TIME);
	}

	/**
	 * ���.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CPhysics::Release()
	{
		SAFE_DELETE(DynamicWorld_);
		SAFE_DELETE(ConstraintSolver_);
		SAFE_DELETE(OverlappingPairCache_);
		SAFE_DELETE(CollisionDispatcher_);
		SAFE_DELETE(CollisionConfiguration_);
	}

	/**
	 * ���̂̒ǉ�.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rb	����.
	 */
	void CPhysics::AddRigidBody(RigidBody * rb)
	{
		DynamicWorld_->addRigidBody(rb->GetBody());
	}

	/**
	 * ���̂̍폜.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rb	����.
	 */
	void CPhysics::RemoveRigidBody(RigidBody * rb)
	{
		DynamicWorld_->removeRigidBody(rb->GetBody());
	}

}// namespace nkEngine