#pragma once

namespace nkEngine
{
	class CRigidBody;

	class CPhysics
	{
	public:

		//コンストラクタ
		CPhysics();

		//デストラクタ
		~CPhysics();

		//初期化
		void Init();

		//更新
		void Update();

		//開放
		void Release();

		//ダイナミックワールドを取得
		//return ダイナミックワールド
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return m_DynamicWorld;
		}

		//リジッドボディの追加
		//param[in] リジッドボディ
		void AddRigidBody(CRigidBody* rb);

		//リジッドボディの削除
		//param[in] リジッドボディ
		void RemoveRigidBody(CRigidBody* rb);

		//凸面一掃？
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			m_DynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}

	private:
		btDefaultCollisionConfiguration* m_CollisionConfiguration; //衝突判定配置
		btCollisionDispatcher* m_CollisionDispatcher; //衝突解決処理
		btBroadphaseInterface* m_OverlappingPairCache; //ブロードフェーズ。衝突判定の枝切り
		btSequentialImpulseConstraintSolver* m_ConstraintSolver; //コンストレイントソルバー。拘束条件の解決処理
		btDiscreteDynamicsWorld* m_DynamicWorld; //ワールド
	};
}