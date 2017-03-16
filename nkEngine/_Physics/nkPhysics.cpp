/**
 * @file	_Physics\nkPhysics.cpp
 *
 * 物理ワールドクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPhysics.h"

namespace nkEngine
{

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CPhysics::Init()
	{
		//物理エンジンを初期化。
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

		//重力計算
		DynamicWorld_->setGravity(btVector3(0, -10, 0));
	}

	/**
	 * 更新.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CPhysics::Update()
	{
		DynamicWorld_->stepSimulation(GAME_DELTA_TIME);
	}

	/**
	 * 解放.
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
	 * 剛体の追加.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rb	剛体.
	 */
	void CPhysics::AddRigidBody(RigidBody * rb)
	{
		DynamicWorld_->addRigidBody(rb->GetBody());
	}

	/**
	 * 剛体の削除.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param [in,out]	rb	剛体.
	 */
	void CPhysics::RemoveRigidBody(RigidBody * rb)
	{
		DynamicWorld_->removeRigidBody(rb->GetBody());
	}

}// namespace nkEngine