#include"stdafx.h"
#include"Player.h"
#include"../GameCamera.h"

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;	//�Փ˃t���O�B
	D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
	D3DXVECTOR3 startPos = D3DXVECTOR3(0,0,0); //���C�̎n�_�B
	D3DXVECTOR3 hitNormal = D3DXVECTOR3(0, 0, 0); //�Փ˓_�̖@���B
	btCollisionObject* me = nullptr; //�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	float dist = FLT_MAX; //�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

	//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me
			|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Character)
		{
			//�����ɏՓ˂����Bor �L�����N�^�����̃R���W�����ƏՓ˂����B
			return 0.0f;
		}
		//�Փ˓_�̖@�������������Ă���B
		D3DXVECTOR3 hitNormalTmp = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
		//������Ɩ@���̂Ȃ��p�x�����߂�B
		float angle = D3DXVec3Dot(&hitNormalTmp,&D3DXVECTOR3(0,1,0));
		angle = fabsf(acosf(angle));

		if (angle < 3.14159265 * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
			|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground /*�������̓R���W�����������n�ʂƎw�肳��Ă���B*/)
		{
			//�Փ˂��Ă���B
			isHit = true;
			D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;

			//�Փ˓_�̋��������߂�B
			D3DXVECTOR3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = D3DXVec3Length(&vDist);

			if (dist > distTmp) {
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
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

	//���̂��������B
	SRigidBodyInfo rbInfo;
	rbInfo.Collider = &CapsuleCollider;
	rbInfo.Mass = 0.0f;
	RigidBody.Create(rbInfo);
	btTransform& trans = RigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
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

	//�����Ă���
	float len = D3DXVec3Length(&move);
	if (len > 0.0f)
	{
		ChangeState(StateCode::StateRun);
	}

	//�J�����̐��ʕ����ɍ��킹��
	D3DXVECTOR3 dirForward = MainCamera.GetDirectionForward();
	D3DXVECTOR3 dirRight = MainCamera.GetDirectionRight();
	D3DXVECTOR3 moveDir;
	moveDir.x = dirRight.x * move.x + dirForward.x * move.z;
	moveDir.y = 0.0f;	//Y���͂���Ȃ��B
	moveDir.z = dirRight.z * move.x + dirForward.z * move.z;

	static float MOVE_SPEED = 0.1f;
	move.x = moveDir.x * MOVE_SPEED;
	move.z = moveDir.z * MOVE_SPEED;

	D3DXQuaternionRotationAxis(&Transform.Rotation, &D3DXVECTOR3(0, 1, 0), atan2f(moveDir.x, moveDir.z) + D3DXToRadian(180.0f));

	D3DXVECTOR3 position = Transform.Position;
	D3DXVECTOR3 nextPosition = move + position;
	//�������𒲂ׂ�B
	{
		D3DXVECTOR3 addPos;
		addPos = nextPosition - position;
		position = nextPosition;	//�ړ��̉��m��B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		start.setOrigin(btVector3(position.x, position.y + m_height * 0.5f + m_radius, position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		D3DXVECTOR3 endPos;
		endPos = (D3DXVECTOR3)start.getOrigin();
		if (m_isOnGround == false) {
			if (addPos.y > 0.0f) {
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
				endPos.y -= addPos.y * 0.01f;
			}
			else {
				//�������Ă���ꍇ�͂��̂܂܉��𒲂ׂ�B
				endPos.y += addPos.y;
			}
		}
		else {
			//�n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultGround callback;
		callback.me = RigidBody.GetBody();
		callback.startPos = (D3DXVECTOR3)start.getOrigin();
		//�Փˌ��o�B
		Physics().ConvexSweepTest((const btConvexShape*)CapsuleCollider.GetBody(), start, end, callback);
		if (callback.isHit) {
			//���������B
			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//�����߂��ʁB
			Circle =D3DXVECTOR3(0,0,0);
			Circle = position;
			Circle.y = callback.hitPos.y;//�~�̒��S
			D3DXVECTOR3 v;
			v = Circle - callback.hitPos;
			x = D3DXVec3Length(&v);//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B
			offset = sqrt(max(0.0f, m_radius*m_radius - x*x));//y�̕����������߂�B
			//m_moveSpeed.y = 0.0f;
			//m_isJump = false;
			m_isOnGround = true;
			nextPosition.y = callback.hitPos.y + offset - m_radius;
		}
		else {
			//�n�ʏ�ɂ��Ȃ��B
			m_isOnGround = false;
		}
	}
	//�ړ��m��B
	Transform.Position = nextPosition;
	btRigidBody* btBody = RigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
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
