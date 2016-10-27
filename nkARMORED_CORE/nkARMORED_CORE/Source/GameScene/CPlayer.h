#pragma once

#include"..\Armoredcore\CArmoredCore.h"

class CPlayer : public CGameObject
{
public:
	//�R���X�g���N�^
	CPlayer();
	
	//�f�X�g���N�^
	~CPlayer();

	//������
	void Init()override;

	//�X�V
	void Update()override;
	
	//�`��
	void Render()override;
	
	//�J��
	void Release()override;

	CTransform* GetTrans()
	{
		return &m_trans;
	}

	void SetMesh(LPD3DXMESH mesh)
	{
		jimen = mesh;
	}

	void SetMatrixInv(D3DXMATRIX*  mi)
	{
		jimenwInv = mi;
	}

private:
	//��]
	void Rotation();
	//�ړ�
	void Move();
	//�n�ʂƂ̓����蔻��
	void Collision();

private:
	CLight m_light; //���C�g
	CTransform m_trans; //�g�����X�t�H�[��
	
	//�^�[�Q�b�g�Ɍ������Đi��
	D3DXVECTOR3 m_Target; //�����_
	D3DXVECTOR3 m_direction_Z;
	D3DXVECTOR3 m_direction_X;
	float m_TargetLen;

	//�n�ʂƂ̃��C���b�V������
	LPD3DXMESH jimen;
	D3DXMATRIX* jimenwInv;

	CArmoredCore m_ArmoredCore;

	const float gravity;


	float boost;
	D3DXVECTOR3 move;
};