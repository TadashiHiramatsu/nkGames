#pragma once

class CCollider;

//���̏��
struct SRigidBodyInfo
{
	SRigidBodyInfo():
		Collider(nullptr),
		Mass(0.0f),
		Position(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		Rotation(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
	{

	}
	D3DXVECTOR3 Position; //���W
	D3DXQUATERNION Rotation; //��]
	CCollider* Collider; //�R���C�_�[
	float Mass; //����
};

//���̃N���X
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
	void Release();
	void Create(SRigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return m_RigidBody;
	}
private:
	btRigidBody* m_RigidBody; //����
	btDefaultMotionState* m_MotionState; //���[�V�����X�e�[�g
};