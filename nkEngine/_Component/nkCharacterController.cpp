#include"nkEngine/nkstdafx.h"
#include"nkCharacterController.h"

namespace nkEngine
{
	//衝突したときに呼ばれる関数オブジェクト(地面用)
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;	//衝突フラグ。
		D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);	//衝突点。
		D3DXVECTOR3 startPos = D3DXVECTOR3(0, 0, 0); //レイの始点。
		D3DXVECTOR3 hitNormal = D3DXVECTOR3(0, 0, 0); //衝突点の法線。
		btCollisionObject* me = nullptr; //自分自身。自分自身との衝突を除外するためのメンバ。
		float dist = FLT_MAX; //衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。

							  //衝突したときに呼ばれるコールバック関数。
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me
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
				isHit = true;
				D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;

				//衝突点の距離を求める。
				D3DXVECTOR3 vDist;
				vDist = hitPosTmp - startPos;
				float distTmp = D3DXVec3Length(&vDist);

				if (dist > distTmp) {
					//この衝突点の方が近いので、最近傍の衝突点を更新する。
					hitPos = hitPosTmp;
					hitNormal = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
					dist = distTmp;
				}
			}
			return 0.0f;
		}
	};

	CharacterController::CharacterController() :
		isJump(false),
		isOnGround(true),
		Radius(0.0f),
		Height(0.0f),
		Gravity(-9.8f)
	{
	}

	CharacterController::~CharacterController()
	{
	}

	void CharacterController::Init(float _radius, float _height, const D3DXVECTOR3 & _pos)
	{
		Position = _pos;
		//コリジョン作成
		Radius = _radius;
		Height = _height;
		Collider.Create(Radius, Height);

		//剛体を初期化。
		SRigidBodyInfo rbInfo;
		rbInfo.Collider = &Collider;
		rbInfo.Mass = 0.0f;
		RigidBody.Create(rbInfo);
		btTransform& trans = RigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(Position.x, Position.y, Position.z));
		RigidBody.GetBody()->setUserIndex(CollisionAttr_Character);
		RigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		Physics().AddRigidBody(&RigidBody);
	}

	void CharacterController::Update()
	{
		//速度に重力加速度を加える
		MoveSpeed.y += Gravity * Time().DeltaTime();

		//次の移動先となる座標を計算
		D3DXVECTOR3 nextPos = Position;
		//速度からこのFrameでの移動量を求める
		D3DXVECTOR3 addPos = MoveSpeed;
		addPos *= Time().DeltaTime();
		nextPos += addPos;

		//下方向を調べる。
		{
			D3DXVECTOR3 addPos;
			addPos = nextPos - Position;

			Position = nextPos;	//移動の仮確定。
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//始点はカプセルコライダーの中心。
			start.setOrigin(btVector3(Position.x, Position.y + Height * 0.5f + Radius, Position.z));
			//終点は地面上にいない場合は1m下を見る。
			//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
			//地面上にいなくて降下中の場合はそのまま落下先を調べる。
			D3DXVECTOR3 endPos;
			endPos = (D3DXVECTOR3)start.getOrigin();
			if (isOnGround == false) {
				if (addPos.y > 0.0f) {
					//ジャンプ中とかで上昇中。
					//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる。
					endPos.y -= addPos.y * 0.01f;
				}
				else {
					//落下している場合はそのまま下を調べる。
					endPos.y += addPos.y;
				}
			}
			else {
				//地面上にいない場合は1m下を見る。
				endPos.y -= 1.0f;
			}
			end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
			SweepResultGround callback;
			callback.me = RigidBody.GetBody();
			callback.startPos = (D3DXVECTOR3)start.getOrigin();
			//衝突検出。
			Physics().ConvexSweepTest((const btConvexShape*)Collider.GetBody(), start, end, callback);
			if (callback.isHit) {
				//当たった。
				D3DXVECTOR3 Circle;
				float x = 0.0f;
				float offset = 0.0f;	//押し戻す量。
				Circle = D3DXVECTOR3(0, 0, 0);
				Circle = Position;
				Circle.y = callback.hitPos.y;//円の中心
				D3DXVECTOR3 v;
				v = Circle - callback.hitPos;
				x = D3DXVec3Length(&v);//物体の角とプレイヤーの間の横幅の距離が求まる。
				offset = sqrt(max(0.0f, Radius*Radius - x*x));//yの平方根を求める。
				
				MoveSpeed.y = 0.0f;
				isJump = false;
				isOnGround = true;
				nextPos.y = callback.hitPos.y + offset - Radius;
			}
			else {
				//地面上にいない。
				isOnGround = false;
			}
		}
		//移動確定。
		Position = nextPos;
		btRigidBody* btBody = RigidBody.GetBody();
		//剛体を動かす。
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(Position.x, Position.y, Position.z));
	}

	void CharacterController::RemoveRigidBody()
	{
		Physics().RemoveRigidBody(&RigidBody);
	}
}