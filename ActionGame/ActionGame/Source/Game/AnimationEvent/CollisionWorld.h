#pragma once

#include"nkEngine/_Physics/nkSphereCollider.h"

class CollisionWorld
{
public:
	//属性
	enum EnAttr
	{
		enDamageToEnemy,	//敵にダメージを与える
		enDamageToPlayer,	//プレイヤーにダメージを与える
	};

	//コリジョンデータ
	class Collision
	{
	public:
		float Radius; //半径
		D3DXVECTOR3 Position; //中心
		float Life; //寿命
		float Damage; //ダメージ量
		EnAttr Attr; //属性
		int GroupID; //コリジョンのグループID
		float Time; //タイム
		shared_ptr<btCollisionObject> CollisionObject; //コリジョンオブジェクト
		CSphereCollider SphereCollider; //球体コライダー
	};

public:

	//コンストラクタ
	CollisionWorld();
	
	//デストラクタ
	~CollisionWorld();

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Render();

	//コリジョンを追加
	inline void CollisionWorld::Add(float _Radius, const D3DXVECTOR3 & _Pos, float _Life, int _Damage, EnAttr _Attr, int _GroupID)
	{
		CollisionPtr col = CollisionPtr(new Collision);
		col->Radius = _Radius;
		col->Position = _Pos;
		col->Life = _Life;
		col->Attr = _Attr;
		col->Time = 0.0f;
		col->Damage = _Damage;
		col->GroupID = _GroupID;
		col->SphereCollider.Create(_Radius);
		col->CollisionObject.reset(new btCollisionObject);
		col->CollisionObject->setCollisionShape(col->SphereCollider.GetBody());
		btTransform worldTrans;
		worldTrans.setIdentity();
		worldTrans.setOrigin(btVector3(_Pos.x, _Pos.y, _Pos.z));
		col->CollisionObject->setWorldTransform(worldTrans);
		col->CollisionObject->setUserPointer(col.get());
		m_Collisions.push_back(col);

		m_CollisionWorld->addCollisionObject(col->CollisionObject.get());
	}

	//重なっているダメージコリジョンを取得する
	const Collision* FindOverlappedDamageCollision(EnAttr _Attr, const D3DXVECTOR3& _Pos, float _Radius)const;
	const Collision* FindOverlappedDamageCollision(EnAttr _Attr, btCollisionObject* _ColObject)const;

private:
	typedef shared_ptr<Collision> CollisionPtr;
	//コリジョンを登録する
	list<CollisionPtr> m_Collisions;
	//コリジョンワールド
	unique_ptr<btCollisionWorld> m_CollisionWorld;
	//コリジョンコンフィグ
	unique_ptr<btDefaultCollisionConfiguration> m_CollisionConfig;
	//衝突解決処理
	unique_ptr<btCollisionDispatcher> m_CollisionDispatcher;
	//ブロードフェーズ。衝突判定の枝切り
	unique_ptr<btBroadphaseInterface> m_BroadphaseInterface;
};

extern CollisionWorld* g_CollisionWorld;