#pragma once

#include"CParts.h"

#include"CHead.h"
#include"CCore.h"
#include"CLeftArm.h"
#include"CRightArm.h"
#include"CLeg.h"

class CArmoredCore :public CGameObject
{
public:

	//�R���X�g���N�^
	CArmoredCore();

	//�f�X�g���N�^
	~CArmoredCore();

	//������
	virtual void Init()override;

	//�X�V
	virtual void Update()override;

	//�`��
	virtual void Render()override;

	//�J��
	virtual void Release()override;

	//�g�����X�t�H�[���̐ݒ�
	void SetTranceform(CTransform* trans)
	{
		m_Tranceform = trans;
	}

	//���C�g�̐ݒ�
	void SetLight(CLight* light)
	{
		m_Light = light;
	}

	//�J�����̐ݒ�
	void SetCamera(CCamera* camera)
	{
		m_Camera = camera;
	}

private:
	CTransform* m_Tranceform;
	CLight* m_Light;
	CCamera* m_Camera;

	//���f�������e�X�g�p
	CHead m_Head;
	CCore m_Core;
	CLeftArm m_LeftArm;
	CRightArm m_RightArm;
	CLeg m_Leg;
};