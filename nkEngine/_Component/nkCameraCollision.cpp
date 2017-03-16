/**
* �J�����̃R���W�����N���X�̎���.
*/
#include"nkEngine/nkstdafx.h"
#include"nkCameraCollision.h"

namespace nkEngine
{

	/**
	* �Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g.
	*/
	struct ConvexSweepCallbackS : public btCollisionWorld::ClosestConvexResultCallback
	{
	public:
		
		/**
		* �R���X�g���N�^.
		*/
		ConvexSweepCallbackS() :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f))
		{
		}

		/**
		* �����̃R�[���o�b�N�֐�.
		*/
		virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{

			if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionAttr_Character)
			{
				//�L�����N�^�[�͖���.
				return 1.0f;
			}

			//�Փ�.
			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}

	};

	/**
	* ������.
	*
	* @param radius	�J�����̔��a.
	* @param posdir	�J�����̎��_�����|�C���^.
	* @param tar	�J�����̒����_���W�|�C���^.
	* @param dis	�J�����̒����_���王�_�̋���
	*/
	void CameraCollision::Start(float radius, const Vector3* posdir, const Vector3* tar)
	{

		//�J�����̎��_��ݒ�
		CameraPosDirection_ = posdir;
		//�J�����̒����_��ݒ�
		CameraTarget_ = tar;

		//���a��ݒ�.
		Radius_ = radius;
		//�R���C�_�[�쐬
		Collider_.Create(Radius_);

	}

	/**
	* �X�V.
	*/
	void CameraCollision::Update()
	{
		//�J�����̎��_���v�Z
		Vector3 pos = *CameraPosDirection_;
		pos.Scale(DefaultDistance_);
		pos.Add(*CameraTarget_);

		//�����_���王�_�ւ̃x�N�g��.
		Vector3 toTarget;

		toTarget.Sub(pos, *CameraTarget_);

		if (toTarget.LengthSq() < FLT_EPSILON)
		{
			//���_�ƒ����_���قړ������W�ɂ���̔�������Ȃ�.
			return;
		}

		//���C���쐬����.
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();

		//�����_���X�^�[�g�ʒu�ɐݒ�
		btStart.setOrigin(btVector3(CameraTarget_->x, CameraTarget_->y, CameraTarget_->z));
		//���_���G���h�ʒu�ɐݒ�
		btEnd.setOrigin(btVector3(pos.x, pos.y, pos.z));
		
		//�R�[���o�b�N�I�u�W�F�N�g.
		ConvexSweepCallbackS callback;

		Physics().ConvexSweepTest((const btConvexShape*)Collider_.GetBody(), btStart, btEnd, callback);

		if (callback.hasHit())
		{
			//���_�ƒ����_�̊Ԃɏ�Q�����������̂ŋ������k�߂�.

			//�Փ˂������W.
			Vector3 hitpos;
			hitpos.Set(callback.m_hitPointWorld);
			
			//�Փ˂������W���W���璍���_�ւ̃x�N�g��.
			Vector3 toHitPos;
			toHitPos.Sub(*CameraTarget_, hitpos);

			//�Փ˂������W���W���璍���_�ւ̋���.
			float len = toHitPos.Length();

			//�ʏ�̋��������Z����ΐݒ�.
			Distance_ = min(DefaultDistance_,len - Radius_);
		}
		else
		{
			//������ʏ�ݒ�.
			Distance_ = DefaultDistance_;
		}
	
	}

}