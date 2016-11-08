#include"stdafx.h"
#include"CollisionWorld.h"


namespace 
{
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
	public:
		//コリジョンオブジェクト
		btCollisionObject* queryCollisionObject = nullptr;
		CollisionWorld::Collision* hitObject = nullptr; //衝突しているコリジョンデータ
		float distSq = FLT_MAX; //?
		CollisionWorld::EnAttr queryAttr = CollisionWorld::enDamageToEnemy; //調べるコリジョン属性

	public:
		virtual btScalar addSingleResult(btManifoldPoint& _cp, const btCollisionObjectWrapper* _colObj0Wrap, int _partId0, int _index0, const btCollisionObjectWrapper* _colObj1Wrap, int _partId1, int _index1)override
		{
			//二つのコリジョンデータからポジションを求める
			const D3DXVECTOR3* vCol0Pos = (D3DXVECTOR3*)(&_colObj0Wrap->getWorldTransform().getOrigin());
			const D3DXVECTOR3* vCol1Pos = (D3DXVECTOR3*)(&_colObj1Wrap->getWorldTransform().getOrigin());
		
			//長さを求める
			D3DXVECTOR3 vDist;
			vDist = *vCol0Pos - *vCol1Pos;
			float distTmpSq = D3DXVec3Length(&vDist);

			CollisionWorld::Collision* hitObjectTmp;

			if (distTmpSq < distSq)
			{
				//こちらのほうが近い
				if (queryCollisionObject == _colObj0Wrap->getCollisionObject())
				{
					hitObjectTmp = (CollisionWorld::Collision*)_colObj1Wrap->getCollisionObject()->getUserPointer();
				}
				else
				{
					hitObjectTmp = (CollisionWorld::Collision*)_colObj0Wrap->getCollisionObject()->getUserPointer();
				}
				if (hitObjectTmp->Attr == queryAttr)
				{
					distSq = distTmpSq;
					hitObject = hitObjectTmp;
				}
			}
			return 0.0f;
		}
	};
}

CollisionWorld::CollisionWorld()
{
}

CollisionWorld::~CollisionWorld()
{
}

void CollisionWorld::Init()
{
	m_CollisionConfig.reset(new btDefaultCollisionConfiguration);
	m_CollisionDispatcher.reset(new btCollisionDispatcher(m_CollisionConfig.get()));
	m_BroadphaseInterface.reset(new btDbvtBroadphase());
	m_CollisionWorld.reset(new btCollisionWorld(m_CollisionDispatcher.get(), m_BroadphaseInterface.get(), m_CollisionConfig.get()));
}

void CollisionWorld::Update()
{
	list<CollisionPtr>::iterator it = m_Collisions.begin();
	while (it != m_Collisions.end())
	{
		(*it)->Time += Time().DeltaTime();
		if ((*it)->Time > (*it)->Life)
		{
			//死亡
			m_CollisionWorld->removeCollisionObject((*it)->CollisionObject.get());
			it = m_Collisions.erase(it);
		}
		else
		{
			it++;
		}
	}
	//有効なら更新
	m_CollisionWorld->updateAabbs();
}

void CollisionWorld::Render()
{
}

const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(EnAttr _Attr, const D3DXVECTOR3 & _Pos, float _Radius) const
{
	for (auto& col : m_Collisions)
	{
		if (col->Attr == _Attr)
		{
			float t = col->Radius + _Radius;
			D3DXVECTOR3 diff;
			diff = col->Position - _Pos;
			if (D3DXVec3LengthSq(&diff) < t * t)
			{
				//衝突
				return col.get();
			}
		}
	}
	return nullptr;
}

const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(EnAttr _Attr, btCollisionObject * _ColObject) const
{
	MyContactResultCallback callback;
	callback.queryCollisionObject = _ColObject;
	callback.queryAttr = _Attr;
	m_CollisionWorld->contactTest(_ColObject, callback);

	return callback.hitObject;
}
