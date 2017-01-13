/**
 * @file Source\Game\AnimationEvent\CollisionWorld.cpp
 *
 * �R���W�������[���h�N���X�̎���.
 */
#include"stdafx.h"
#include"CollisionWorld.h"

//�������
namespace 
{

	/**
	 * �R�[���o�b�N�\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
	public:

		/**
		 * Adds a single result.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 *
		 * @param [in,out] cp		   The cp.
		 * @param 		   colObj0Wrap The col object 0 wrap.
		 * @param 		   partId0	   The part identifier 0.
		 * @param 		   index0	   The index 0.
		 * @param 		   colObj1Wrap The col object 1 wrap.
		 * @param 		   partId1	   The first part identifier.
		 * @param 		   index1	   The first index.
		 *
		 * @return A btScalar.
		 */
		virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
		{

			//��̃R���W�����f�[�^����|�W�V���������߂�
			const D3DXVECTOR3* vCol0Pos = (D3DXVECTOR3*)(&colObj0Wrap->getWorldTransform().getOrigin());
			const D3DXVECTOR3* vCol1Pos = (D3DXVECTOR3*)(&colObj1Wrap->getWorldTransform().getOrigin());
		
			//���������߂�
			D3DXVECTOR3 vDist;
			vDist = *vCol0Pos - *vCol1Pos;
			float distTmpSq = D3DXVec3Length(&vDist);

			//�R���W�����쐬
			CollisionWorld::Collision* hitObjectTmp;

			if (distTmpSq < DistSq_)
			{
				//������̂ق����߂�
				if (QueryCollisionObject_ == colObj0Wrap->getCollisionObject())
				{
					hitObjectTmp = (CollisionWorld::Collision*)colObj1Wrap->getCollisionObject()->getUserPointer();
				}
				else
				{
					hitObjectTmp = (CollisionWorld::Collision*)colObj0Wrap->getCollisionObject()->getUserPointer();
				}

				if (hitObjectTmp->Attr_ == QueryAttr_)
				{
					DistSq_ = distTmpSq;
					HitObject_ = hitObjectTmp;
				}

			}

			return 0.0f;
		}

	public:

		/** �R���W�����I�u�W�F�N�g. */
		btCollisionObject* QueryCollisionObject_ = nullptr;
		/** �Փ˂��Ă���R���W�����f�[�^. */
		CollisionWorld::Collision* HitObject_ = nullptr;
		/** ?�BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l */
		float DistSq_ = FLT_MAX;
		/** ���ׂ�R���W��������. */
		CollisionWorld::AttributeE QueryAttr_ = CollisionWorld::DamageToEnemy;

	};

}// namespace

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
CollisionWorld::CollisionWorld()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
CollisionWorld::~CollisionWorld()
{
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void CollisionWorld::Start()
{
	//�R���t�B�O�̏�����
	CollisionConfig_.reset(new btDefaultCollisionConfiguration);
	//�Փˉ��������̏�����
	CollisionDispatcher_.reset(new btCollisionDispatcher(CollisionConfig_.get()));
	//�u���[�h�t�F�[�Y�̏�����
	BroadphaseInterface_.reset(new btDbvtBroadphase());

	//�R���W�������[���h�̏�����
	CollisionWorld_.reset(new btCollisionWorld(CollisionDispatcher_.get(), BroadphaseInterface_.get(), CollisionConfig_.get()));

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void CollisionWorld::Update()
{
	
	//�C�e���[�^�쐬
	auto it = CollisionList_.begin();

	while (it != CollisionList_.end())
	{
		//���Ԃ����Z
		(*it)->Time_ += Time().DeltaTime();

		//�������s���Ă��Ȃ���
		if ((*it)->Time_ > (*it)->Life_)
		{
			//���S
			CollisionWorld_->removeCollisionObject((*it)->CollisionObject_.get());
			it = CollisionList_.erase(it);
		}
		else
		{
			it++;
		}
	}

	//�L���Ȃ�X�V
	CollisionWorld_->updateAabbs();

}

/**
* �d�Ȃ��Ă���_���[�W�R���W�������擾����.
* �����ƈʒu�Ƒ傫������Z�o.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param attr   ����.
* @param pos    �ʒu.
* @param radius �傫��.
*
* @return Null if it fails, else the found overlapped damage collision.
*/
const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(AttributeE attr, const D3DXVECTOR3 & pos, float radius) const
{
	for (auto& col : CollisionList_)
	{
		//����������
		if (col->Attr_ == attr)
		{
			float t = col->Radius_ + radius;

			D3DXVECTOR3 diff;
			diff = col->Position_ - pos;
			
			if (D3DXVec3LengthSq(&diff) < t * t)
			{
				//�Փ�
				return col.get();
			}

		}

	}

	return nullptr;
}
/**
* �d�Ȃ��Ă���_���[�W�R���W�������擾����.
* �����ƃR���W�����I�u�W�F�N�g����Z�o.
*
* @author HiramatsuTadashi
* @date 2017/01/11
*
* @param 		   attr		 ����.
* @param [in,out] colObject �R���W�����I�u�W�F�N�g.
*
* @return Null if it fails, else the found overlapped damage collision.
*/
const CollisionWorld::Collision* CollisionWorld::FindOverlappedDamageCollision(AttributeE attr, btCollisionObject * colObject) const
{
	MyContactResultCallback callback;

	callback.QueryCollisionObject_ = colObject;
	callback.QueryAttr_ = attr;
	
	CollisionWorld_->contactTest(colObject, callback);

	return callback.HitObject_;
}
