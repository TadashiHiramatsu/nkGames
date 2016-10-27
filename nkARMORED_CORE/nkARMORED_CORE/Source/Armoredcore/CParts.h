#pragma once

#include"../Physics/CMeshCollider.h"
#include"../Physics/CRigidBody.h"

class CParts : public CGameObject
{
public:

	//�R���X�g���N�^
	CParts();

	//�f�X�g���N�^
	~CParts();

	//������
	virtual void Init()override;

	//�X�V
	virtual void Update()override;

	//�`��
	virtual void Render()override;

	//�J��
	virtual void Release()override;

	//�ǂݍ���
	void LoadModel(const char* filepass);

	//���̏�����
	void InitRigidBody();

	inline CACModelRender* GetACModel()
	{
		return &m_ACModel;
	}

	inline CAnimation* GetAnimation()
	{
		return &m_Animation;
	}

	inline D3DXMATRIX* GetMatrix(const char* pass)
	{
		return m_ACModel.FindBoneWorldMatrix(pass);
	}

protected:
	CACModelRender m_ACModel; //���f��
	CTransform m_Transform; //�g�����X�t�H�[��
	CAnimation m_Animation; //�A�j���[�V�����Ǘ�

	bool m_isBreak;
	D3DXMATRIX* m_mWorld; //���[���h�s��
	CMeshCollider m_MeshCollider; //���b�V���R���C�_�[
	CRigidBody m_RigidBody; //����
};
