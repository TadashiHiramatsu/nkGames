#include"nkEngine/nkstdafx.h"
#include"nkCharacterController.h"

namespace nkEngine
{
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;	//�Փ˃t���O�B
		D3DXVECTOR3 hitPos = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
		D3DXVECTOR3 startPos = D3DXVECTOR3(0, 0, 0); //���C�̎n�_�B
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
			float angle = D3DXVec3Dot(&hitNormalTmp, &D3DXVECTOR3(0, 1, 0));
			angle = fabsf(acosf(angle));

			if (angle < 3.14159265 * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
				|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground) /*�������̓R���W�����������n�ʂƎw�肳��Ă���B*/
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
		//�R���W�����쐬
		Radius = _radius;
		Height = _height;
		Collider.Create(Radius, Height);

		//���̂��������B
		SRigidBodyInfo rbInfo;
		rbInfo.Collider = &Collider;
		rbInfo.Mass = 0.0f;
		RigidBody.Create(rbInfo);
		btTransform& trans = RigidBody.GetBody()->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(Position.x, Position.y, Position.z));
		RigidBody.GetBody()->setUserIndex(CollisionAttr_Character);
		RigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		Physics().AddRigidBody(&RigidBody);
	}

	void CharacterController::Update()
	{
		//���x�ɏd�͉����x��������
		MoveSpeed.y += Gravity * Time().DeltaTime();

		//���̈ړ���ƂȂ���W���v�Z
		D3DXVECTOR3 nextPos = Position;
		//���x���炱��Frame�ł̈ړ��ʂ����߂�
		D3DXVECTOR3 addPos = MoveSpeed;
		addPos *= Time().DeltaTime();
		nextPos += addPos;

		//�������𒲂ׂ�B
		{
			D3DXVECTOR3 addPos;
			addPos = nextPos - Position;

			Position = nextPos;	//�ړ��̉��m��B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
			start.setOrigin(btVector3(Position.x, Position.y + Height * 0.5f + Radius, Position.z));
			//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
			//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
			//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
			D3DXVECTOR3 endPos;
			endPos = (D3DXVECTOR3)start.getOrigin();
			if (isOnGround == false) {
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
			Physics().ConvexSweepTest((const btConvexShape*)Collider.GetBody(), start, end, callback);
			if (callback.isHit) {
				//���������B
				D3DXVECTOR3 Circle;
				float x = 0.0f;
				float offset = 0.0f;	//�����߂��ʁB
				Circle = D3DXVECTOR3(0, 0, 0);
				Circle = Position;
				Circle.y = callback.hitPos.y;//�~�̒��S
				D3DXVECTOR3 v;
				v = Circle - callback.hitPos;
				x = D3DXVec3Length(&v);//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B
				offset = sqrt(max(0.0f, Radius*Radius - x*x));//y�̕����������߂�B
				
				MoveSpeed.y = 0.0f;
				isJump = false;
				isOnGround = true;
				nextPos.y = callback.hitPos.y + offset - Radius;
			}
			else {
				//�n�ʏ�ɂ��Ȃ��B
				isOnGround = false;
			}
		}
		//�ړ��m��B
		Position = nextPos;
		btRigidBody* btBody = RigidBody.GetBody();
		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(Position.x, Position.y, Position.z));
	}

	void CharacterController::RemoveRigidBody()
	{
		Physics().RemoveRigidBody(&RigidBody);
	}
}