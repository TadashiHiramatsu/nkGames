/**
 * @file Source\Game\Monster\IMonster.cpp
 *
 * �����X�^�[�̊��N���X�̎���.
 */
#include"stdafx.h"
#include"IMonster.h"

#include"..\GameCamera.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IMonster::IMonster():
	Radius_(0.4f),
	Height_(0.3f),
	Hp_(10),
	Distance_(10),
	toPlayerMaxDis_(20),
	PlayerAttackDis_(0.3f),
	WaitingTime_(4),
	WaitingLT_(0),
	Destination_(D3DXVECTOR3(0, 0, 0))
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IMonster::~IMonster()
{
	Release();
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Start()
{
	//�g�����X�t�H�[���̐ݒ�
	ModelRender_.SetTransform(&Transform_);
	//���C�g�̐ݒ�
	ModelRender_.SetLight(&Light_);
	//�J����
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//�V���h�E���V�[�o�L���X�^
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Update()
{
	//�g�����X�t�H�[���̍X�V
	Transform_.Update();

	//���f���̍X�V
	ModelRender_.Update();

}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Render()
{
	//���f���̕\��
	ModelRender_.Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IMonster::Release()
{
	//�L�����N�^�[�R���g���[���̍��̂��폜
	CharacterController_.RemoveRigidBody();
}