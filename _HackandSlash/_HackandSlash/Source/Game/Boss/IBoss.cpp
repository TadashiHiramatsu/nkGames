/**
* �{�X�̊��N���X�̎���.
*/
#include"stdafx.h"
#include"IBoss.h"

#include"../GameCamera.h"
#include"../GameLight.h"

/**
* ������.
*/
void IBoss::Start()
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
*/
void IBoss::Update()
{
	//�g�����X�t�H�[���̍X�V
	Transform_.Update();

	//���f���̍X�V
	ModelRender_.Update();
}

/**
* �`��.
*/
void IBoss::Render()
{
	//���f���̕\��
	ModelRender_.Render();
}

/**
* ���.
*/
void IBoss::Release()
{
}
