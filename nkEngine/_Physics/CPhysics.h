#pragma once

namespace nkEngine
{
	class CRigidBody;

	class CPhysics
	{
	public:

		//�R���X�g���N�^
		CPhysics();

		//�f�X�g���N�^
		~CPhysics();

		//������
		void Init();

		//�X�V
		void Update();

		//�J��
		void Release();

		//�_�C�i�~�b�N���[���h���擾
		//return �_�C�i�~�b�N���[���h
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return m_DynamicWorld;
		}

		//���W�b�h�{�f�B�̒ǉ�
		//param[in] ���W�b�h�{�f�B
		void AddRigidBody(CRigidBody* rb);

		//���W�b�h�{�f�B�̍폜
		//param[in] ���W�b�h�{�f�B
		void RemoveRigidBody(CRigidBody* rb);

		//�ʖʈ�|�H
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			m_DynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}

	private:
		btDefaultCollisionConfiguration* m_CollisionConfiguration; //�Փ˔���z�u
		btCollisionDispatcher* m_CollisionDispatcher; //�Փˉ�������
		btBroadphaseInterface* m_OverlappingPairCache; //�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�
		btSequentialImpulseConstraintSolver* m_ConstraintSolver; //�R���X�g���C���g�\���o�[�B�S�������̉�������
		btDiscreteDynamicsWorld* m_DynamicWorld; //���[���h
	};
}