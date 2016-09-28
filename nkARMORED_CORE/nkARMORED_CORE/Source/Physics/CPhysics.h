#pragma once

class CRigidBody;

class CPhysics : public CGameObject
{
public:

	//コンストラクタ
	CPhysics();

	//デストラクタ
	~CPhysics();
	
	//初期化
	void Init()override;

	//更新
	void Update()override;

	//描画
	void Render()override;

	//開放
	void Release()override;

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

	//なぁにこれぇ
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f)
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

extern CPhysics g_Physics;