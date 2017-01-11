/**
 * @file _Component\nkCharacterController.cpp
 *
 * �L�����N�^�[�R���g���[���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkCharacterController.h"

//�������
namespace
{
	using namespace nkEngine;

	/**
	* �Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp).
	*
	* @author HiramatsuTadashi
	* @date 2017/01/10
	*/
	struct SweepResultGroundS : public btCollisionWorld::ConvexResultCallback
	{
	public:

		/**
		* �Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�.
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
				isHit_ = true;
				D3DXVECTOR3 hitPosTmp = *(D3DXVECTOR3*)&convexResult.m_hitPointLocal;

				//�Փ˓_�̋��������߂�B
				D3DXVECTOR3 vDist;
				vDist = hitPosTmp - StartPos_;
				float distTmp = D3DXVec3Length(&vDist);

				if (Dist_ > distTmp)
				{
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					HitPos_ = hitPosTmp;
					HitNormal_ = *(D3DXVECTOR3*)&convexResult.m_hitNormalLocal;
					Dist_ = distTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** �Փ˃t���O. */
		bool isHit_ = false;
		/** �Փ˓_. */
		D3DXVECTOR3 HitPos_ = D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f);
		/** ���C�̎n�_. */
		D3DXVECTOR3 StartPos_ = D3DXVECTOR3(0, 0, 0);
		/** �Փ˓_�̖@��. */
		D3DXVECTOR3 HitNormal_ = D3DXVECTOR3(0, 0, 0);
		/** �������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o. */
		btCollisionObject* MyCol_ = nullptr;
		/** �Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l. */
		float Dist_ = FLT_MAX;

	};

}

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
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
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CharacterController::~CharacterController()
	{
	}

	/**
	 * ������.
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

		//�|�W�V�����R�s�[
		Position_ = pos;
		
		//�R���W�����쐬
		Radius_ = radius;
		Height_ = height;
		Collider_.Create(Radius_, Height_);

		//���̂��������B
		RigidBodyInfoS rbInfo;
		rbInfo.Collider_ = &Collider_;
		rbInfo.Mass_ = 0.0f;
		RigidBody_.Create(rbInfo);

		btTransform& trans = RigidBody_.GetBody()->getWorldTransform();

		//���̂̈ʒu���X�V�B
		trans.setOrigin(btVector3(Position_.x, Position_.y, Position_.z));
		RigidBody_.GetBody()->setUserIndex(CollisionAttr_Character);
		RigidBody_.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		
		//�������[���h�ɍ��̂�ǉ�
		Physics().AddRigidBody(&RigidBody_);

	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CharacterController::Update()
	{

		//���x�ɏd�͉����x��������
		MoveSpeed_.y += Gravity_ * Time().DeltaTime();

		//���̈ړ���ƂȂ���W���v�Z
		D3DXVECTOR3 nextPos = Position_;

		//���x���炱��Frame�ł̈ړ��ʂ����߂�
		D3DXVECTOR3 addPos = MoveSpeed_;
		addPos *= Time().DeltaTime();
		nextPos += addPos;

		//�������𒲂ׂ�B
		{
			D3DXVECTOR3 addPos;
			addPos = nextPos - Position_;

			//�ړ��̉��m��B
			Position_ = nextPos;

			//�X�^�[�g�ƃG���h���쐬
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();

			//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
			start.setOrigin(btVector3(Position_.x, Position_.y + Height_ * 0.5f + Radius_, Position_.z));

			//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
			//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
			//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
			D3DXVECTOR3 endPos;
			endPos = (D3DXVECTOR3)start.getOrigin();

			if (isOnGround_ == false)
			{
				//���ł���
				if (addPos.y > 0.0f)
				{
					//�W�����v���Ƃ��ŏ㏸���B
					//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
					endPos.y -= addPos.y * 0.01f;
				}
				else
				{
					//�������Ă���ꍇ�͂��̂܂܉��𒲂ׂ�B
					endPos.y += addPos.y;
				}
			}
			else
			{
				//�n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
				endPos.y -= 1.0f;
			}

			end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));

			SweepResultGroundS callback;
			callback.MyCol_ = RigidBody_.GetBody();
			callback.StartPos_ = (D3DXVECTOR3)start.getOrigin();

			//�Փˌ��o�B
			Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

			if (callback.isHit_)
			{
				//���������B
				D3DXVECTOR3 Circle;
				float x = 0.0f;

				//�����߂��ʁB
				float offset = 0.0f;
				Circle = D3DXVECTOR3(0, 0, 0);
				Circle = Position_;
				Circle.y = callback.HitPos_.y;//�~�̒��S

				D3DXVECTOR3 v;
				v = Circle - callback.HitPos_;

				//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B
				x = D3DXVec3Length(&v);

				//y�̕����������߂�B
				offset = sqrt(max(0.0f, Radius_ * Radius_ - x*x));

				MoveSpeed_.y = 0.0f;
				isJump_ = false;
				isOnGround_ = true;

				nextPos.y = callback.HitPos_.y + offset - Radius_;
			}
			else
			{
				//�n�ʏ�ɂ��Ȃ��B
				isOnGround_ = false;
			}
		}

		//�ړ��m��B
		Position_ = nextPos;
		btRigidBody* btBody = RigidBody_.GetBody();

		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();

		//���̂̈ʒu���X�V�B
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