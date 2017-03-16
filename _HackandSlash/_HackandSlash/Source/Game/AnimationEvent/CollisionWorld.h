/**
 * @file Source\Game\AnimationEvent\CollisionWorld.h
 *
 * コリジョンワールドクラスの定義.
 */
#pragma once

#include"nkEngine/_Physics/nkSphereCollider.h"

/**
 * コリジョンワールドクラス.
 * 属性を持った球体コライダーを登録することができる.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class CollisionWorld : public IGameObject
{
public:

	/** 属性. */
	enum class AttributeE
	{
		DamageToEnemy,	//!< 敵にダメージを与える
		DamageToPlayer,	//!< プレイヤーにダメージを与える
	};

	/**
	 * コリジョンデータクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	class Collision
	{
	public:

		/** 半径. */
		float Radius_;
		/** 中心. */
		Vector3 Position_;
		/** 寿命. */
		float Life_;
		/** ダメージ量. */
		float Damage_;
		/** 属性. */
		AttributeE Attr_;
		/** コリジョンのグループID. */
		int GroupID_;
		/** タイム. */
		float Time_;
		/** コリジョンオブジェクト. */
		shared_ptr<btCollisionObject> CollisionObject_;
		/** 球体コライダー. */
		SphereCollider SphereCollider_;

	};

public:

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	CollisionWorld()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~CollisionWorld()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * コリジョンを追加.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param radius  The radius.
	 * @param pos	  The position.
	 * @param life    The life.
	 * @param damage  The damage.
	 * @param attr    The attribute.
	 * @param groupID Identifier for the group.
	 */
	inline void CollisionWorld::Add(float radius, const Vector3 & pos, float life, int damage, AttributeE attr, int groupID)
	{
		CollisionPtrT col = CollisionPtrT(new Collision);

		col->Radius_ = radius;
		col->Position_ = pos;
		col->Life_ = life;
		col->Attr_ = attr;
		col->Time_ = 0.0f;
		col->Damage_ = damage;
		col->GroupID_ = groupID;
		
		col->SphereCollider_.Create(radius);
		
		col->CollisionObject_.reset(new btCollisionObject);
		col->CollisionObject_->setCollisionShape(col->SphereCollider_.GetBody());
		
		btTransform worldTrans;
		
		worldTrans.setIdentity();
		worldTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
		
		col->CollisionObject_->setWorldTransform(worldTrans);
		col->CollisionObject_->setUserPointer(col.get());
		
		//コリジョンに登録
		CollisionList_.push_back(col);

		//コリジョンワールドに登録
		CollisionWorld_->addCollisionObject(col->CollisionObject_.get());

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
	const Collision* FindOverlappedDamageCollision(AttributeE attr, const Vector3& pos, float radius)const;
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
	const Collision* FindOverlappedDamageCollision(AttributeE attr, btCollisionObject* colObject)const;

private:

	/** shared_ptr<Collision> コリジョンのポインタ. */
	typedef shared_ptr<Collision> CollisionPtrT;

	/** コリジョンを登録する. */
	list<CollisionPtrT> CollisionList_;
	/** コリジョンワールド. */
	unique_ptr<btCollisionWorld> CollisionWorld_;
	/** コリジョンコンフィグ. */
	unique_ptr<btDefaultCollisionConfiguration> CollisionConfig_;
	/** 衝突解決処理. */
	unique_ptr<btCollisionDispatcher> CollisionDispatcher_;
	/** ブロードフェーズ。衝突判定の枝切り. */
	unique_ptr<btBroadphaseInterface> BroadphaseInterface_;

};

/** グローバル. */
extern CollisionWorld* g_CollisionWorld;