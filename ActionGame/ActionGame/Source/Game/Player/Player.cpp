#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

//衝突したときに呼ばれる関数オブジェクト(地面用)
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;	//衝突フラグ。
	D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);	//衝突点。
	D3DXVECTOR3 startPos = D3DXVECTOR3(0,0,0); //レイの始点。
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
		float angle = D3DXVec3Dot(&hitNormalTmp,&D3DXVECTOR3(0,1,0));
		angle = fabsf(acosf(angle));

		if (angle < 3.14159265 * 0.3f		//地面の傾斜が54度より小さいので地面とみなす。
			|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground /*もしくはコリジョン属性が地面と指定されている。*/)
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

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Model.Load("Player.X",&Animation);
	Model.SetTransform(&Transform);
	Model.SetLight(&Light);
	Model.SetCamera(MainCamera.GetCamera());

	MainCamera.SetPlayerTranceform(&Transform);

	Transform.Position = D3DXVECTOR3(0, 1, 0);

	m_radius = 0.4f;
	m_height = 0.3f;
	CapsuleCollider.Create(m_radius, m_height);

	//剛体を初期化。
	SRigidBodyInfo rbInfo;
	rbInfo.Collider = &CapsuleCollider;
	rbInfo.Mass = 0.0f;
	RigidBody.Create(rbInfo);
	btTransform& trans = RigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(Transform.Position.x, Transform.Position.y, Transform.Position.z));
	RigidBody.GetBody()->setUserIndex(CollisionAttr_Character);
	RigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	Physics().AddRigidBody(&RigidBody);
}

void Player::Update()
{
	ChangeState(StateCode::StateWaiting);
	D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
	if (Input.GetKeyButton(KeyCode::W))
	{
		move += D3DXVECTOR3(0, 0, 1);
	}
	if (Input.GetKeyButton(KeyCode::S))
	{
		move += D3DXVECTOR3(0, 0, -1);
	}
	if (Input.GetKeyButton(KeyCode::A))
	{
		move += D3DXVECTOR3(-1, 0, 0);
	}
	if (Input.GetKeyButton(KeyCode::D))
	{
		move += D3DXVECTOR3(1, 0, 0);
	}

	//走っている
	float len = D3DXVec3Length(&move);
	if (len > 0.0f)
	{
		ChangeState(StateCode::StateRun);
	}

	//カメラの正面方向に合わせる
	D3DXVECTOR3 dirForward = MainCamera.GetDirectionForward();
	D3DXVECTOR3 dirRight = MainCamera.GetDirectionRight();
	D3DXVECTOR3 moveDir;
	moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
	moveDir.y = 0.0f;	//Y軸はいらない。
	moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

	static float MOVE_SPEED = 0.1f;
	move.x = moveDir.x * MOVE_SPEED;
	move.z = moveDir.z * MOVE_SPEED;

	D3DXQuaternionRotationAxis(&Transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));

	D3DXVECTOR3 position = Transform.Position;
	D3DXVECTOR3 nextPosition = move + position;
	//下方向を調べる。
	{
		D3DXVECTOR3 addPos;
		addPos = nextPosition - position;
		position = nextPosition;	//移動の仮確定。
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//始点はカプセルコライダーの中心。
		start.setOrigin(btVector3(position.x, position.y + m_height * 0.5f + m_radius, position.z));
		//終点は地面上にいない場合は1m下を見る。
		//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
		//地面上にいなくて降下中の場合はそのまま落下先を調べる。
		D3DXVECTOR3 endPos;
		endPos = (D3DXVECTOR3)start.getOrigin();
		if (m_isOnGround == false) {
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
		Physics().ConvexSweepTest((const btConvexShape*)CapsuleCollider.GetBody(), start, end, callback);
		if (callback.isHit) {
			//当たった。
			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//押し戻す量。
			Circle =D3DXVECTOR3(0,0,0);
			Circle = position;
			Circle.y = callback.hitPos.y;//円の中心
			D3DXVECTOR3 v;
			v = Circle - callback.hitPos;
			x = D3DXVec3Length(&v);//物体の角とプレイヤーの間の横幅の距離が求まる。
			offset = sqrt(max(0.0f, m_radius*m_radius - x*x));//yの平方根を求める。
			//m_moveSpeed.y = 0.0f;
			//m_isJump = false;
			m_isOnGround = true;
			nextPosition.y = callback.hitPos.y + offset - m_radius;
		}
		else {
			//地面上にいない。
			m_isOnGround = false;
		}
	}
	//移動確定。
	Transform.Position = nextPosition;
	btRigidBody* btBody = RigidBody.GetBody();
	//剛体を動かす。
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(Transform.Position.x, Transform.Position.y, Transform.Position.z));

	AnimationControl();
	Model.Update();
}

void Player::Render()
{
	Model.Render();
}

void Player::Release()
{
	Model.Release();
}

void Player::ChangeState(StateCode _NextState)
{
	state = _NextState;
}

void Player::AnimationControl()
{
	float time = 1.0f / 120.0f;
	switch (state)
	{
	case AnimationWaiting:
		PlayAnimation(AnimationCode::AnimationWaiting, 0.1f);
		break;
	case StateRun:
		PlayAnimation(AnimationCode::AnimationRun, 0.1f);
		time = 1.0f / 6000.0f;
		break;
	default:
		break;
	}
	Animation.Update(time);
}

void Player::PlayAnimation(AnimationCode _AnimCode, float interpolateTime)
{
	if (Animation.GetNowAnimation() != _AnimCode)
	{
		Animation.PlayAnimation(_AnimCode);
	}
}
