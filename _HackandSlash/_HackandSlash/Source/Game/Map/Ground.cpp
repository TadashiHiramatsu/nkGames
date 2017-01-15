/**
 * @file Source\Game\Map\Ground.cpp
 *
 * �O���E���h�N���X�̎���.
 */
#include"stdafx.h"
#include"Ground.h"

#include"..\GameCamera.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
Ground::Ground()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
Ground::~Ground()
{
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Start()
{
	//���f���̃��[�h
	ModelRender_.Load("Ground.X",nullptr);
	//�g�����X�t�H�[���̐ݒ�
	ModelRender_.SetTransform(&Transform_);
	//���C�g�̐ݒ�
	ModelRender_.SetLight(&Light_);
	//�J�����̐ݒ�
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	//�V���h�E�L���X�^�[�̐ݒ�true.
	ModelRender_.SetShadowCasterFlag(true);
	//�V���h�E���V�[�o�[�̐ݒ�true.
	ModelRender_.SetShadowReceiverFlag(true);

	//�@���}�b�v�̐ݒ�
	Normal_.Load("ground4_Normal.tga");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("ground4_Specular.tga");
	ModelRender_.SetSpecMap(&Specular_);

	//�X�V
	Update();

	//���[���h�s��̎擾
	WorldMatrix_ = ModelRender_.FindBoneWorldMatrix("Plane001");

	//���b�V���R���C�_�[�̍쐬
	MeshCollider_.Create(&ModelRender_, WorldMatrix_);
	
	//���̂̍쐬
	RigidBodyInfoS rbInfo;
	rbInfo.Collider_ = &MeshCollider_;
	rbInfo.Mass_ = 0.0f;
	RigidBody_.Create(rbInfo);

	//�O���E���h�^�O��ݒ�
	RigidBody_.GetBody()->setUserIndex(ECollisionAttr::CollisionAttr_Ground);

	//�������[���h�ɒǉ�
	Physics().AddRigidBody(&RigidBody_);

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Update()
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
 * @date 2017/01/10
 */
void Ground::Render()
{
	//���f���̕`��
	ModelRender_.Render();

}

/**
 * ���.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void Ground::Release()
{
	//���f���̉��
	ModelRender_.Release();

}