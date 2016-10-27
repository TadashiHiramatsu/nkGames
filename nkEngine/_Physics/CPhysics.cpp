#include"nkEngine/nkstdafx.h"
#include"CPhysics.h"
#include"CRigidBody.h"

namespace nkEngine
{
	CPhysics::CPhysics() :
		m_CollisionConfiguration(nullptr),
		m_CollisionDispatcher(nullptr),
		m_OverlappingPairCache(nullptr),
		m_ConstraintSolver(nullptr),
		m_DynamicWorld(nullptr)
	{
	}

	CPhysics::~CPhysics()
	{
		Release();
	}

	void CPhysics::Init()
	{
		//物理エンジンを初期化。
		m_CollisionConfiguration = new btDefaultCollisionConfiguration();

		m_CollisionDispatcher = new	btCollisionDispatcher(m_CollisionConfiguration);

		m_OverlappingPairCache = new btDbvtBroadphase();

		m_ConstraintSolver = new btSequentialImpulseConstraintSolver;

		m_DynamicWorld = new btDiscreteDynamicsWorld(
			m_CollisionDispatcher,
			m_OverlappingPairCache,
			m_ConstraintSolver,
			m_CollisionConfiguration
		);

		//重力計算
		m_DynamicWorld->setGravity(btVector3(0, -10, 0));
	}

	void CPhysics::Update()
	{
		m_DynamicWorld->stepSimulation(GAME_DELTA_TIME);
	}

	void CPhysics::Release()
	{
		SAFE_DELETE(m_DynamicWorld);
		SAFE_DELETE(m_ConstraintSolver);
		SAFE_DELETE(m_OverlappingPairCache);
		SAFE_DELETE(m_CollisionDispatcher);
		SAFE_DELETE(m_CollisionConfiguration);
	}

	void CPhysics::AddRigidBody(CRigidBody * rb)
	{
		m_DynamicWorld->addRigidBody(rb->GetBody());
	}

	void CPhysics::RemoveRigidBody(CRigidBody * rb)
	{
		m_DynamicWorld->removeRigidBody(rb->GetBody());
	}

}