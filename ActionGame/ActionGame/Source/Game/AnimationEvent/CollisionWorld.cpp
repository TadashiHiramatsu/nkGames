/**
 * @file Source\Game\AnimationEvent\CollisionWorld.cpp
 *
 * コリジョンワールドクラスの実装.
 */
#include"stdafx.h"
#include"CollisionWorld.h"

//無名空間
namespace 
{

	/**
	 * コールバック構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
	public:

		/**
		 * Adds a single result.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 *
		 * @param [in,out] cp		   The cp.
		 * @param 		   colObj0Wrap The col object 0 wrap.
		 * @param 		   partId0	   The part identifier 0.
		 * @param 		   index0	   The index 0.
		 * @param 		   colObj1Wrap The col object 1 wrap.
		 * @param 		   partId1	   The first part identifier.
		 * @param 		   index1	   The first index.
		 *
		 * @return A btScalar.
		 */
		virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
		{

			//二つのコリジョンデータからポジションを求める
			const D3DXVECTOR3* vCol0Pos = (D3DXVECTOR3*)(&colObj0Wrap->getWorldTransform().getOrigin());
			const D3DXVECTOR3* vCol1Pos = (D3DXVECTOR3*)(&colObj1Wrap->getWorldTransform().getOrigin());
		
			//長さを求める
			D3DXVECTOR3 vDist;
			vDist = *vCol0Pos - *vCol1Pos;
			float distTmpSq = D3DXVec3Length(&vDist);

			//コリジョン作成
			CollisionWorld::Collision* hitObjectTmp;

			if (distTmpSq < DistSq_)
			{
				//こちらのほうが近い
				if (QueryCollisionObject_ == colObj0Wrap->getCollisionObject())
				{
					hitObjectTmp = (CollisionWorld::Collision*)colObj1Wrap->getCollisionObject()->getUserPointer();
				}
				else
				{
					hitObjectTmp = (CollisionWorld::Collision*)colObj0Wrap->getCollisionObject()->getUserPointer();
				}

				if (hitObjectTmp->Attr_ == QueryAttr_)
				{
					DistSq_ = distTmpSq;
					HitObject_ = hitObjectTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** コリジョンオブジェクト. */
		btCollisionObject* QueryCollisionObject_ = nullptr;
		/** 衝突しているコリジョンデータ. */
		CollisionWorld::Collision* HitObject_ = nullptr;
		/** ?。FLT_MAXは単精度の浮動小数点が取りうる最大の値 */
		float DistSq_ = FLT_MAX;
		/** 調べるコリジョン属性. */
		CollisionWorld::AttributeE QueryAttr_ = CollisionWorld::DamageToEnemy;

	};

}// namespace

/**
 * コンストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
CollisionWorld::CollisionWorld()
{
}

/**
 * デストラクタ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
CollisionWorld::~CollisionWorld()
{
}

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void CollisionWorld::Start()
{
	//コンフィグの初期化
	CollisionConfig_.reset(new btDefaultCollisionConfiguration);
	//衝突解決処理の初期化
	CollisionDispatcher_.reset(new btCollisionDispatcher(CollisionConfig_.get()));
	//ブロードフェーズの初期化
	BroadphaseInterface_.reset(new btDbvtBroadphase());

	//コリジョンワールドの初期化
	CollisionWorld_.reset(new btCollisionWorld(CollisionDispatcher_.get(), BroadphaseInterface_.get(), CollisionConfig_.get()));

}

/**
 * 更新.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void CollisionWorld::Update()
{
	
	//イテレータ作成
	auto it = CollisionList_.begin();

	while (it != CollisionList_.end())
	{
		//時間を加算
		(*it)->Time_ += Time().DeltaTime();

		//寿命が尽きていないか
		if ((*it)->Time_ > (*it)->Life_)
		{
			//死亡
			CollisionWorld_->removeCollisionObject((*it)->CollisionObject_.get());
			it = CollisionList_.erase(it);
		}
		else
		{
			it++;
		}
	}

	//有効なら更新
	CollisionWorld_->updateAabbs();

}

/**
* 重なっているダメージコリジョンを取得する.
* 属性と位置と大きさから算出.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param attr   属性.
* @param pos    位置.
* @param radius 大きさ.
*
* @return Null if it fails, else the found overlapped damage collision.
*/
const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(AttributeE attr, const D3DXVECTOR3 & pos, float radius) const
{
	for (auto& col : CollisionList_)
	{
		//属性が同じ
		if (col->Attr_ == attr)
		{
			float t = col->Radius_ + radius;

			D3DXVECTOR3 diff;
			diff = col->Position_ - pos;
			
			if (D3DXVec3LengthSq(&diff) < t * t)
			{
				//衝突
				return col.get();
			}

		}

	}

	return nullptr;
}
/**
* 重なっているダメージコリジョンを取得する.
* 属性とコリジョンオブジェクトから算出.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param 		   attr		 属性.
* @param [in,out] colObject コリジョンオブジェクト.
*
* @return Null if it fails, else the found overlapped damage collision.
*/
const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(AttributeE attr, btCollisionObject * colObject) const
{
	MyContactResultCallback callback;

	callback.QueryCollisionObject_ = colObject;
	callback.QueryAttr_ = attr;
	
	CollisionWorld_->contactTest(colObject, callback);

	return callback.HitObject_;
}
