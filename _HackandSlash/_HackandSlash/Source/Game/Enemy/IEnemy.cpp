/**
 * @file Source\Game\Monster\IEnemy.cpp
 *
 * �G�̊��N���X�̎���.
 */
#include"stdafx.h"
#include"IEnemy.h"

#include"..\GameCamera.h"
#include"../GameLight.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IEnemy::IEnemy():
	Radius_(0.3f),
	Height_(0.5f),
	Hp_(50),
	Distance_(10),
	toPlayerMaxDis_(20),
	PlayerAttackDis_(0.3f),
	WaitingTime_(4),
	WaitingLT_(0)
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
IEnemy::~IEnemy()
{
	Release();
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Start()
{
	//�g�����X�t�H�[���̐ݒ�
	ModelRender_.SetTransform(&Transform_);
	//���C�g�̐ݒ�
	ModelRender_.SetLight(g_GameLight->GetLight());
	//�J����
	ModelRender_.SetCamera(g_MainCamera->GetCamera());

	//�V���h�E���V�[�o�L���X�^
	ModelRender_.SetShadowCasterFlag(true);
	ModelRender_.SetShadowReceiverFlag(true);

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void IEnemy::Update()
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
void IEnemy::Render()
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
void IEnemy::Release()
{
	
}
