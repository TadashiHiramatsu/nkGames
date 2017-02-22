/**
 * @file Source\Game\Map\Skybox.cpp
 *
 * �X�J�C�{�b�N�X�N���X�̎���.
 */
#include"stdafx.h"
#include"Skybox.h"

#include"..\GameCamera.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Start()
{
	//���f�������[�h
	ModelRender_.Load("Skybox.x", nullptr);
	//�J�����̐ݒ�
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//�g�����X�t�H�[���̐ݒ�
	ModelRender_.SetTransform(&Transform_);
	//���C�g�̐ݒ�
	ModelRender_.SetLight(&Light_);

	//ModelRender_.SetFogParam(ModelRender::FogFuncE::FogFuncHeight, 400.0f, 0.0f);

	//�������ő�ɂ��ă��C�e�B���O������
	Light_.SetAmbientLight(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//Light_.SetEmissionLightColor(D3DXVECTOR3(0.1, 0.1, 0.1));
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Update()
{
	//�e�q�֌W�ɕύX���Ă���������
	//�|�W�V�������v���C���[�̈ʒu��
	Transform_.Position_ = Player_->Transform_.Position_;

	//�g�����X�t�H�[���̍X�V
	Transform_.Update();

	//���f���̍X�V
	ModelRender_.Update();

}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Render()
{
	//���f����\��
	ModelRender_.Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Skybox::Release()
{
	//���f���̉��
	ModelRender_.Release();

}