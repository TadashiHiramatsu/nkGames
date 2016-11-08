#pragma once

#include"nkEngine/_Physics/nkSphereCollider.h"

class CollisionWorld
{
public:
	//����
	enum EnAttr
	{
		enDamageToEnemy,	//�G�Ƀ_���[�W��^����
		enDamageToPlayer,	//�v���C���[�Ƀ_���[�W��^����
	};

	//�R���W�����f�[�^
	class Collision
	{
	public:
		float Radius; //���a
		D3DXVECTOR3 Position; //���S
		float Life; //����
		float Damage; //�_���[�W��
		EnAttr Attr; //����
		int GroupID; //�R���W�����̃O���[�vID
		float Time; //�^�C��
		shared_ptr<btCollisionObject> CollisionObject; //�R���W�����I�u�W�F�N�g
		CSphereCollider SphereCollider; //���̃R���C�_�[
	};

public:

	//�R���X�g���N�^
	CollisionWorld();
	
	//�f�X�g���N�^
	~CollisionWorld();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�R���W������ǉ�
	inline void CollisionWorld::Add(float _Radius, const D3DXVECTOR3 & _Pos, float _Life, int _Damage, EnAttr _Attr, int _GroupID)
	{
		CollisionPtr col = CollisionPtr(new Collision);
		col->Radius = _Radius;
		col->Position = _Pos;
		col->Life = _Life;
		col->Attr = _Attr;
		col->Time = 0.0f;
		col->Damage = _Damage;
		col->GroupID = _GroupID;
		col->SphereCollider.Create(_Radius);
		col->CollisionObject.reset(new btCollisionObject);
		col->CollisionObject->setCollisionShape(col->SphereCollider.GetBody());
		btTransform worldTrans;
		worldTrans.setIdentity();
		worldTrans.setOrigin(btVector3(_Pos.x, _Pos.y, _Pos.z));
		col->CollisionObject->setWorldTransform(worldTrans);
		col->CollisionObject->setUserPointer(col.get());
		m_Collisions.push_back(col);

		m_CollisionWorld->addCollisionObject(col->CollisionObject.get());
	}

	//�d�Ȃ��Ă���_���[�W�R���W�������擾����
	const Collision* FindOverlappedDamageCollision(EnAttr _Attr, const D3DXVECTOR3& _Pos, float _Radius)const;
	const Collision* FindOverlappedDamageCollision(EnAttr _Attr, btCollisionObject* _ColObject)const;

private:
	typedef shared_ptr<Collision> CollisionPtr;
	//�R���W������o�^����
	list<CollisionPtr> m_Collisions;
	//�R���W�������[���h
	unique_ptr<btCollisionWorld> m_CollisionWorld;
	//�R���W�����R���t�B�O
	unique_ptr<btDefaultCollisionConfiguration> m_CollisionConfig;
	//�Փˉ�������
	unique_ptr<btCollisionDispatcher> m_CollisionDispatcher;
	//�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�
	unique_ptr<btBroadphaseInterface> m_BroadphaseInterface;
};

extern CollisionWorld* g_CollisionWorld;