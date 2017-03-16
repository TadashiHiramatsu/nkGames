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
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);

			//上方向と法線のなす角度を求める。
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));

			if (angle < 3.14159265 * 0.3f		//地面の傾斜が54度より小さいので地面とみなす。
				|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground) /*もしくはコリジョン属性が地面と指定されている。*/
			{
				//衝突している。
				isHit_ = true;
				
				//ヒットした座標.
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);

				//衝突点の距離を求める。
				Vector3 vDist;
				vDist.Sub(hitPosTmp,StartPos_);

				float distTmp = vDist.Length();

				if (Dist_ > distTmp)
				{
					//この衝突点の方が近いので、最近傍の衝突点を更新する。
					HitPos_ = hitPosTmp;
					HitNormal_.Set(convexResult.m_hitNormalLocal);
					Dist_ = distTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** 衝突フラグ. */
		bool isHit_ = false;
		/** 衝突点. */
		Vector3 HitPos_ = Vector3(0.0f, -FLT_MAX, 0.0f);
		/** レイの始点. */
		Vector3 StartPos_ = Vector3::Zero;
		/** 衝突点の法線. */
		Vector3 HitNormal_ = Vector3::Zero;
		/** 自分自身。自分自身との衝突を除外するためのメンバ. */
		btCollisionObject* MyCol_ = nullptr;
		/** 衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値. */
		float Dist_ = FLT_MAX;

	};

	/**
	* 衝突したときに呼ばれるコールバック(壁用).
	*/
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
	public:

		/**
		* 衝突したときに呼ばれるコールバック関数.
		*/
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == MyCol_) 
			{
				//自分に衝突した.
				return 0.0f;
			}

			//衝突点の法線を引っ張ってくる。
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);

			//上方向と衝突点の法線のなす角度を求める。
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));

			if (angle >= PI * 0.3f
				|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionAttr_Character) 
			{
				//地面の傾斜が54度以上なので壁とみなす。
				//もしくはコリジョン属性がキャラクタなので壁とみなす。

				//衝突した.
				isHit_ = true;

				//衝突した位置を取得.
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);

				//交点との距離を調べる。
				Vector3 vDist;
				vDist.Sub(hitPosTmp, StartPosition_);
				vDist.y = 0.0f;

				float distTmp = vDist.Length();

				if (distTmp < Dist_)
				{
					//この衝突点の方が近いので、最近傍の衝突点を更新する。
					HitPosition_ = hitPosTmp;
					Dist_ = distTmp;
					HitNormal_ = hitNormalTmp;
				}
			}
			return 0.0f;
		}

	public:

		/** 衝突フラグ. */
		bool isHit_ = false;
		/** 衝突点. */
		Vector3 HitPosition_ = Vector3(0.0f, -FLT_MAX, 0.0f);
		/** レイの始点. */
		Vector3 StartPosition_ = Vector3::Up;
		/** 衝突点の法線. */
		Vector3 HitNormal_ = Vector3::Up;
		/** 自分自身。自分自身との衝突を除外するためのメンバ. */
		btCollisionObject* MyCol_ = nullptr;
		/** 衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値. */
		float Dist_ = FLT_MAX;

	};

}

namespace nkEngine
{

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param radius 半径.
	 * @param height 高さ.
	 * @param pos    座標.
	 */
	void CharacterController::Init(float radius, float height, const Vector3& pos)
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
		Vector3 nextPos = Position_;

		//速度からこのFrameでの移動量を求める
		Vector3 addPos = MoveSpeed_;
		addPos.Scale(Time().DeltaTime());
		nextPos.Add(addPos);

		Vector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();

		//XZ平面での衝突検出と衝突解決を行う。
		{
			int loopCount = 0;
			while (true) 
			{
				//現在の座標から次の移動先へ向かうベクトルを求める。
				
				//加算する座標.
				Vector3 addPos;
				addPos.Sub(nextPos, Position_);

				//高さを消す.
				Vector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;

				if (addPosXZ.Length() < FLT_EPSILON)
				{
					//XZ平面で動きがないので調べる必要なし。
					//FLT_EPSILONは1より大きい、最小の値との差分を表す定数。
					//とても小さい値のことです。
					break;
				}

				//カプセルコライダーの中心座標 + 0.2の座標をposTmpに求める。
				Vector3 posTmp = Position_;
				posTmp.y += Height_ * 0.5f + Radius_ + 0.2f;

				//レイを作成。
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				
				//始点はカプセルコライダーの中心座標 + 0.2の座標をposTmpに求める。
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				
				//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
				end.setOrigin(btVector3(nextPos.x, posTmp.y, nextPos.z));

				SweepResultWall callback;
				
				//コリジョンを設定.
				callback.MyCol_ = RigidBody_.GetBody();

				//スタート座標.
				callback.StartPosition_ = posTmp;
				
				//衝突検出。
				Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

				if (callback.isHit_) 
				{
					//当たった。
					//壁。
					Vector3 vT0, vT1;

					//XZ平面上での移動後の座標をvT0に、交点の座標をvT1に設定する。
					vT0 = Vector3(nextPos.x, 0.0f, nextPos.z);
					vT1 = Vector3(callback.HitPosition_.x, 0.0f, callback.HitPosition_.z);

					//めり込みが発生している移動ベクトルを求める。
					Vector3 vMerikomi;
					vMerikomi.Sub(vT0 ,vT1);

					//XZ平面での衝突した壁の法線を求める。。
					Vector3 hitNormalXZ = callback.HitNormal_;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();

					//めり込みベクトルを壁の法線に射影する。
					float fT0 = hitNormalXZ.Dot(vMerikomi);

					//押し戻し返すベクトルを求める。
					//押し返すベクトルは壁の法線に射影されためり込みベクトル+半径。
					Vector3 vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + Radius_);

					//押し戻す.
					nextPos.Add(vOffset);

					Vector3 currentDir;
					currentDir.Sub(nextPos, Position_);
					currentDir.y = 0.0f;
					currentDir.Normalize();

					if (currentDir.Dot(originalXZDir) < 0.0f)
					{
						//角に入った時のキャラクタの振動を防止するために、
						//移動先が逆向きになったら移動をキャンセルする。
						nextPos.x = Position_.x;
						nextPos.z = Position_.z;
						break;
					}
				}
				else 
				{
					//どことも当たらないので終わり。
					break;
				}

				loopCount++;
				if (loopCount == 5) 
				{
					break;
				}
			}
		}
		//XZの移動は確定。
		Position_.x = nextPos.x;
		Position_.z = nextPos.z;

		//下方向を調べる。
		{
			Vector3 addPos;
			addPos.Sub(nextPos , Position_);

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
			Vector3 endPos;
			endPos.Set(start.getOrigin());

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
			callback.StartPos_.Set(start.getOrigin());

			//衝突検出。
			Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

			if (callback.isHit_)
			{
				//当たった。
				Vector3 Circle = Position_;

				MoveSpeed_.y = 0.0f;
				isJump_ = false;
				isOnGround_ = true;
				nextPos.y = callback.HitPos_.y;
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