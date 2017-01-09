/**
 * @file	_Physics\nkPhysics.h
 *
 * 物理ワールドクラスの定義.
 */
#pragma once

#include"nkRigidBody.h"

namespace nkEngine
{

	/**
	 * 物理ワールドクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CPhysics
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CPhysics();

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CPhysics();

		/**
		 * 初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Init();

		/**
		 * 更新.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Update();

		/**
		 * 開放.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Release();

		/**
		 * ダイナミックワールドの取得.
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
		 * 剛体の追加.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rb	剛体.
		 */
		void AddRigidBody(CRigidBody* rb);

		/**
		 * 剛体の削除.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @param [in,out]	rb	剛体.
		 */
		void RemoveRigidBody(CRigidBody* rb);

		/**
		 * 凸面一掃？.
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

		/** 衝突判定配置. */
		btDefaultCollisionConfiguration* CollisionConfiguration_;
		/** 衝突解決処理. */
		btCollisionDispatcher* CollisionDispatcher_;
		/** ブロードフェーズ。衝突判定の枝切り. */
		btBroadphaseInterface* OverlappingPairCache_;
		/** コンストレイントソルバー。拘束条件の解決処理. */
		btSequentialImpulseConstraintSolver* ConstraintSolver_;
		/** ワールド. */
		btDiscreteDynamicsWorld* DynamicWorld_;

	};

}// namespace nkEngine