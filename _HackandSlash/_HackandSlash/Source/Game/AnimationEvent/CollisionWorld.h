/**
 * @file Source\Game\AnimationEvent\CollisionWorld.h
 *
 * �R���W�������[���h�N���X�̒�`.
 */
#pragma once

#include"nkEngine/_Physics/nkSphereCollider.h"

/**
 * �R���W�������[���h�N���X.
 * ���������������̃R���C�_�[��o�^���邱�Ƃ��ł���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class CollisionWorld : public IGameObject
{
public:

	/** ����. */
	enum class AttributeE
	{
		DamageToEnemy,	//!< �G�Ƀ_���[�W��^����
		DamageToPlayer,	//!< �v���C���[�Ƀ_���[�W��^����
	};

	/**
	 * �R���W�����f�[�^�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	class Collision
	{
	public:

		/** ���a. */
		float Radius_;
		/** ���S. */
		Vector3 Position_;
		/** ����. */
		float Life_;
		/** �_���[�W��. */
		float Damage_;
		/** ����. */
		AttributeE Attr_;
		/** �R���W�����̃O���[�vID. */
		int GroupID_;
		/** �^�C��. */
		float Time_;
		/** �R���W�����I�u�W�F�N�g. */
		shared_ptr<btCollisionObject> CollisionObject_;
		/** ���̃R���C�_�[. */
		SphereCollider SphereCollider_;

	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	CollisionWorld()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~CollisionWorld()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * �R���W������ǉ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param radius  The radius.
	 * @param pos	  The position.
	 * @param life    The life.
	 * @param damage  The damage.
	 * @param attr    The attribute.
	 * @param groupID Identifier for the group.
	 */
	inline void CollisionWorld::Add(float radius, const Vector3 & pos, float life, int damage, AttributeE attr, int groupID)
	{
		CollisionPtrT col = CollisionPtrT(new Collision);

		col->Radius_ = radius;
		col->Position_ = pos;
		col->Life_ = life;
		col->Attr_ = attr;
		col->Time_ = 0.0f;
		col->Damage_ = damage;
		col->GroupID_ = groupID;
		
		col->SphereCollider_.Create(radius);
		
		col->CollisionObject_.reset(new btCollisionObject);
		col->CollisionObject_->setCollisionShape(col->SphereCollider_.GetBody());
		
		btTransform worldTrans;
		
		worldTrans.setIdentity();
		worldTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
		
		col->CollisionObject_->setWorldTransform(worldTrans);
		col->CollisionObject_->setUserPointer(col.get());
		
		//�R���W�����ɓo�^
		CollisionList_.push_back(col);

		//�R���W�������[���h�ɓo�^
		CollisionWorld_->addCollisionObject(col->CollisionObject_.get());

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
	const Collision* FindOverlappedDamageCollision(AttributeE attr, const Vector3& pos, float radius)const;
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
	const Collision* FindOverlappedDamageCollision(AttributeE attr, btCollisionObject* colObject)const;

private:

	/** shared_ptr<Collision> �R���W�����̃|�C���^. */
	typedef shared_ptr<Collision> CollisionPtrT;

	/** �R���W������o�^����. */
	list<CollisionPtrT> CollisionList_;
	/** �R���W�������[���h. */
	unique_ptr<btCollisionWorld> CollisionWorld_;
	/** �R���W�����R���t�B�O. */
	unique_ptr<btDefaultCollisionConfiguration> CollisionConfig_;
	/** �Փˉ�������. */
	unique_ptr<btCollisionDispatcher> CollisionDispatcher_;
	/** �u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�. */
	unique_ptr<btBroadphaseInterface> BroadphaseInterface_;

};

/** �O���[�o��. */
extern CollisionWorld* g_CollisionWorld;