/**
 * @file _Component\nkCharacterController.cpp
 *
 * キャラクターコントローラクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCharacterController.h"

//無名空間
namespace
{
	using namespace nkEngine;

	/**
	* 衝突したときに呼ばれる関数オブジェクト(地面用).
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	struct SweepResultGroundS : public btCollisionWorld::ConvexResultCallback
	{
	public:

		/**
		* 衝突したときに呼ばれるコールバック関数.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/10
		*
		* @param [in,out] convexResult		  The convex result.
		* @param 		   normalInWorldSpace True to normal in world space.
		*
		* @return A btScalar.
		*/
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == MyCol_
				|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Character)
			{
				//自分に衝突した。or キャラクタ属性のコリジョンと衝突した。
				return 0.0f;
			}

			//衝突点の法線を引っ張ってくる。
			D3DXVECTOR3 hitNormalTmp = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;

			//上方向と法線のなす角度を求める。
			float angle = D3DXVec3Dot(&hitNormalTmp, &D3DXVECTOR3(0, 1, 0));
			angle = fabsf(acosf(angle));

			if (angle < 3.14159265 * 0.3f		//地面の傾斜が54度より小さいので地面とみなす。
				|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground) /*もしくはコリジョン属性が地面と指定されている。*/
			{
				//衝突している。
				isHit_ = true;
				D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;

				//衝突点の距離を求める。
				D3DXVECTOR3 vDist;
				vDist = hitPosTmp - StartPos_;
				float distTmp = D3DXVec3Length(&vDist);

				if (Dist_ > distTmp)
				{
					//この衝突点の方が近いので、最近傍の衝突点を更新する。
					HitPos_ = hitPosTmp;
					HitNormal_ = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
					Dist_ = distTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** 衝突フラグ. */
		bool isHit_ = false;
		/** 衝突点. */
		D3DXVECTOR3 HitPos_ = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);
		/** レイの始点. */
		D3DXVECTOR3 StartPos_ = D3DXVECTOR3(0, 0, 0);
		/** 衝突点の法線. */
		D3DXVECTOR3 HitNormal_ = D3DXVECTOR3(0, 0, 0);
		/** 自分自身。自分自身との衝突を除外するためのメンバ. */
		btCollisionObject* MyCol_ = nullptr;
		/** 衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値. */
		float Dist_ = FLT_MAX;

	};

}

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CharacterController::CharacterController() :
		isJump_(false),
		isOnGround_(true),
		Radius_(0.0f),
		Height_(0.0f),
		Gravity_(-9.8f),
		MoveSpeed_(D3DXVECTOR3(0,0,0))
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CharacterController::~CharacterController()
	{
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param radius The radius.
	 * @param height The height.
	 * @param pos    The position.
	 */
	void CharacterController::Init(float radius, float height, const D3DXVECTOR3& pos)
	{

		//ポジションコピー
		Position_ = pos;
		
		//コリジョン作成
		Radius_ = radius;
		Height_ = height;
		Collider_.Create(Radius_, Height_);

		//剛体を初期化。
		RigidBodyInfoS rbInfo;
		rbInfo.Collider_ = &Collider_;
		rbInfo.Mass_ = 0.0f;
		RigidBody_.Create(rbInfo);

		btTransform& trans = RigidBody_.GetBody()->getWorldTransform();

		//剛体の位置を更新。
		trans.setOrigin(btVector3(Position_.x, Position_.y, Position_.z));
		RigidBody_.GetBody()->setUserIndex(CollisionAttr_Character);
		RigidBody_.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		
		//物理ワールドに剛体を追加
		Physics().AddRigidBody(&RigidBody_);

	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CharacterController::Update()
	{

		//速度に重力加速度を加える
		MoveSpeed_.y += Gravity_ * Time().DeltaTime();

		//次の移動先となる座標を計算
		D3DXVECTOR3 nextPos = Position_;

		//速度からこのFrameでの移動量を求める
		D3DXVECTOR3 addPos = MoveSpeed_;
		addPos *= Time().DeltaTime();
		nextPos += addPos;

		//下方向を調べる。
		{
			D3DXVECTOR3 addPos;
			addPos = nextPos - Position_;

			//移動の仮確定。
			Position_ = nextPos;

			//スタートとエンドを作成
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();

			//始点はカプセルコライダーの中心。
			start.setOrigin(btVector3(Position_.x, Position_.y + Height_ * 0.5f + Radius_, Position_.z));

			//終点は地面上にいない場合は1m下を見る。
			//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
			//地面上にいなくて降下中の場合はそのまま落下先を調べる。
			D3DXVECTOR3 endPos;
			endPos = (D3DXVECTOR3)start.getOrigin();

			if (isOnGround_ == false)
			{
				//飛んでいる
				if (addPos.y > 0.0f)
				{
					//ジャンプ中とかで上昇中。
					//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる。
					endPos.y -= addPos.y * 0.01f;
				}
				else
				{
					//落下している場合はそのまま下を調べる。
					endPos.y += addPos.y;
				}
			}
			else
			{
				//地面上にいない場合は1m下を見る。
				endPos.y -= 1.0f;
			}

			end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));

			SweepResultGroundS callback;
			callback.MyCol_ = RigidBody_.GetBody();
			callback.StartPos_ = (D3DXVECTOR3)start.getOrigin();

			//衝突検出。
			Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

			if (callback.isHit_)
			{
				//当たった。
				D3DXVECTOR3 Circle;
				float x = 0.0f;

				//押し戻す量。
				float offset = 0.0f;
				Circle = D3DXVECTOR3(0, 0, 0);
				Circle = Position_;
				Circle.y = callback.HitPos_.y;//円の中心

				D3DXVECTOR3 v;
				v = Circle - callback.HitPos_;

				//物体の角とプレイヤーの間の横幅の距離が求まる。
				x = D3DXVec3Length(&v);

				//yの平方根を求める。
				offset = sqrt(max(0.0f, Radius_ * Radius_ - x*x));

				MoveSpeed_.y = 0.0f;
				isJump_ = false;
				isOnGround_ = true;

				nextPos.y = callback.HitPos_.y + offset - Radius_;
			}
			else
			{
				//地面上にいない。
				isOnGround_ = false;
			}
		}

		//移動確定。
		Position_ = nextPos;
		btRigidBody* btBody = RigidBody_.GetBody();

		//剛体を動かす。
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();

		//剛体の位置を更新。
		trans.setOrigin(btVector3(Position_.x, Position_.y, Position_.z));

	}

	/**
	 * Removes the rigid body.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CharacterController::RemoveRigidBody()
	{
		Physics().RemoveRigidBody(&RigidBody_);
	}

}// namespace nkEngine