#pragma once

#include"../Physics/CMeshCollider.h"
#include"../Physics/CBoxCollider.h"
#include"../Physics/CRigidBody.h"

class CGround : public CGameObject
{
public:
	//�R���X�g���N�^
	CGround();

	//�f�X�g���N�^
	~CGround();

	//������
	void Init()override;

	//�X�V
	void Update()override;

	//�`��
	void Render()override;

	//�J��
	void Release()override;

	LPD3DXMESH GetMesh()
	{
		return m_model.GetMesh();
	}

	D3DXMATRIX* GetWorldInv()
	{
		return m_model.GetWorldInv();
	}
private:
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;

	CTexture m_NormalMap; //�@���}�b�v�p�e�N�X�`��

	D3DXMATRIX* m_mWorld; //���[���h�s��
	CMeshCollider m_MeshCollider; //���b�V���R���C�_�[
	CRigidBody m_RigidBody; //����
};