#pragma once

#include"Source\Physics\CCollider.h"

class CBoxCollider : public CCollider
{
public:

	//�R���X�g���N�^
	CBoxCollider();

	//�f�X�g���N�^
	~CBoxCollider();

	//�{�b�N�X�R���C�_�[�쐬
	//param[in] �T�C�Y
	void Create(const D3DXVECTOR3& size);

	//�{�f�B�̎擾
	btCollisionShape* GetBody()override
	{
		return m_Shape;
	}

private:
	btBoxShape* m_Shape; //�{�b�N�X�`��
};