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
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);

			//������Ɩ@���̂Ȃ��p�x�����߂�B
			float angle = hitNormalTmp.Dot(Vector3::Up);
			angle = fabsf(acosf(angle));

			if (angle < 3.14159265 * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
				|| convexResult.m_hitCollisionObject->getUserIndex() == ECollisionAttr::CollisionAttr_Ground) /*�������̓R���W�����������n�ʂƎw�肳��Ă���B*/
			{
				//�Փ˂��Ă���B
				isHit_ = true;
				
				//�q�b�g�������W.
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);

				//�Փ˓_�̋��������߂�B
				Vector3 vDist;
				vDist.Sub(hitPosTmp,StartPos_);

				float distTmp = vDist.Length();

				if (Dist_ > distTmp)
				{
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					HitPos_ = hitPosTmp;
					HitNormal_.Set(convexResult.m_hitNormalLocal);
					Dist_ = distTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** �Փ˃t���O. */
		bool isHit_ = false;
		/** �Փ˓_. */
		Vector3 HitPos_ = Vector3(0.0f, -FLT_MAX, 0.0f);
		/** ���C�̎n�_. */
		Vector3 StartPos_ = Vector3::Zero;
		/** �Փ˓_�̖@��. */
		Vector3 HitNormal_ = Vector3::Zero;
		/** �������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o. */
		btCollisionObject* MyCol_ = nullptr;
		/** �Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l. */
		float Dist_ = FLT_MAX;

	};

	/**
	* �Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N(�Ǘp).
	*/
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
	public:

		/**
		* �Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�.
		*/
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == MyCol_) 
			{
				//�����ɏՓ˂���.
				return 0.0f;
			}

			//�Փ˓_�̖@�������������Ă���B
			Vector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);

			//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�B
			float angle = fabsf(acosf(hitNormalTmp.Dot(Vector3::Up)));

			if (angle >= PI * 0.3f
				|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionAttr_Character) 
			{
				//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
				//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B

				//�Փ˂���.
				isHit_ = true;

				//�Փ˂����ʒu���擾.
				Vector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);

				//��_�Ƃ̋����𒲂ׂ�B
				Vector3 vDist;
				vDist.Sub(hitPosTmp, StartPosition_);
				vDist.y = 0.0f;

				float distTmp = vDist.Length();

				if (distTmp < Dist_)
				{
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					HitPosition_ = hitPosTmp;
					Dist_ = distTmp;
					HitNormal_ = hitNormalTmp;
				}
			}
			return 0.0f;
		}

	public:

		/** �Փ˃t���O. */
		bool isHit_ = false;
		/** �Փ˓_. */
		Vector3 HitPosition_ = Vector3(0.0f, -FLT_MAX, 0.0f);
		/** ���C�̎n�_. */
		Vector3 StartPosition_ = Vector3::Up;
		/** �Փ˓_�̖@��. */
		Vector3 HitNormal_ = Vector3::Up;
		/** �������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o. */
		btCollisionObject* MyCol_ = nullptr;
		/** �Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l. */
		float Dist_ = FLT_MAX;

	};

}

namespace nkEngine
{

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param radius ���a.
	 * @param height ����.
	 * @param pos    ���W.
	 */
	void CharacterController::Init(float radius, float height, const Vector3& pos)
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
		Vector3 nextPos = Position_;

		//���x���炱��Frame�ł̈ړ��ʂ����߂�
		Vector3 addPos = MoveSpeed_;
		addPos.Scale(Time().DeltaTime());
		nextPos.Add(addPos);

		Vector3 originalXZDir = addPos;
		originalXZDir.y = 0.0f;
		originalXZDir.Normalize();

		//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
		{
			int loopCount = 0;
			while (true) 
			{
				//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
				
				//���Z������W.
				Vector3 addPos;
				addPos.Sub(nextPos, Position_);

				//����������.
				Vector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;

				if (addPosXZ.Length() < FLT_EPSILON)
				{
					//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
					//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
					//�ƂĂ��������l�̂��Ƃł��B
					break;
				}

				//�J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				Vector3 posTmp = Position_;
				posTmp.y += Height_ * 0.5f + Radius_ + 0.2f;

				//���C���쐬�B
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				
				//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				
				//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
				end.setOrigin(btVector3(nextPos.x, posTmp.y, nextPos.z));

				SweepResultWall callback;
				
				//�R���W������ݒ�.
				callback.MyCol_ = RigidBody_.GetBody();

				//�X�^�[�g���W.
				callback.StartPosition_ = posTmp;
				
				//�Փˌ��o�B
				Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

				if (callback.isHit_) 
				{
					//���������B
					//�ǁB
					Vector3 vT0, vT1;

					//XZ���ʏ�ł̈ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
					vT0 = Vector3(nextPos.x, 0.0f, nextPos.z);
					vT1 = Vector3(callback.HitPosition_.x, 0.0f, callback.HitPosition_.z);

					//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
					Vector3 vMerikomi;
					vMerikomi.Sub(vT0 ,vT1);

					//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B�B
					Vector3 hitNormalXZ = callback.HitNormal_;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();

					//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
					float fT0 = hitNormalXZ.Dot(vMerikomi);

					//�����߂��Ԃ��x�N�g�������߂�B
					//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
					Vector3 vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + Radius_);

					//�����߂�.
					nextPos.Add(vOffset);

					Vector3 currentDir;
					currentDir.Sub(nextPos, Position_);
					currentDir.y = 0.0f;
					currentDir.Normalize();

					if (currentDir.Dot(originalXZDir) < 0.0f)
					{
						//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
						//�ړ��悪�t�����ɂȂ�����ړ����L�����Z������B
						nextPos.x = Position_.x;
						nextPos.z = Position_.z;
						break;
					}
				}
				else 
				{
					//�ǂ��Ƃ�������Ȃ��̂ŏI���B
					break;
				}

				loopCount++;
				if (loopCount == 5) 
				{
					break;
				}
			}
		}
		//XZ�̈ړ��͊m��B
		Position_.x = nextPos.x;
		Position_.z = nextPos.z;

		//�������𒲂ׂ�B
		{
			Vector3 addPos;
			addPos.Sub(nextPos , Position_);

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
			Vector3 endPos;
			endPos.Set(start.getOrigin());

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
			callback.StartPos_.Set(start.getOrigin());

			//�Փˌ��o�B
			Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), start, end, callback);

			if (callback.isHit_)
			{
				//���������B
				Vector3 Circle = Position_;

				MoveSpeed_.y = 0.0f;
				isJump_ = false;
				isOnGround_ = true;
				nextPos.y = callback.HitPos_.y;
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