/**
 * @file Source\Game\GUI\LifeGage.cpp
 *
 * ���C�t�Q�[�W�N���X�̎���.
 */
#include"stdafx.h"
#include"LifeGage.h"

/**
 * �R���X�g���N�^.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::LifeGage()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
LifeGage::~LifeGage()
{
}

/**
 * ������.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Start()
{
	//�t���[���̉摜�����[�h
	LifeFrameImage_.Load("Image/LifeFrame.png");
	//�g�����X�t�H�[���̐ݒ�
	LifeFrameImage_.SetTransform(&LifeFrameTransform_);

	//�{�̂̉摜�����[�h
	LifeImage_.Load("Image/Life.png");
	//�g�����X�t�H�[���̐ݒ�
	LifeImage_.SetTransform(&LifeTransform_);

	//�e�q�֌W�ݒ�
	LifeTransform_.Parent_ = &LifeFrameTransform_;

	//�傫����ݒ�
	LifeFrameTransform_.Width_ = LifeFrameTransform_.Height_ = 150;
	LifeTransform_.Width_ = LifeTransform_.Height_ = 140;

	//�t���[���̃A���J�[������
	LifeFrameTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomLeft;
	LifeFrameTransform_.Pivot_ = D3DXVECTOR2(0, 0);

	//�{�̂̃A���J�[���t���[���̉�����
	LifeTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomCenter;
	LifeTransform_.Pivot_ = D3DXVECTOR2(0.5, 0);
	//�ʒu�𒲐�
	LifeTransform_.Position_.y = 5;

	//���C�t�̃|�C���^���擾
	MaxLife_ = &Player_->GetParameter().MaxHp_;
	NowLife_ = &Player_->GetParameter().NowHp_;

	//�t�H���g�̏�����
	Life_.Create(20, 15);

}

/**
 * �X�V.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::Update()
{
	//�\���̈�Ƒ傫�����v�Z
	LifeImage_.RectUV_.y = 1.0f - (float)*NowLife_ / (float)*MaxLife_;
	LifeTransform_.Height_ = (float)*NowLife_ / (float)*MaxLife_ * 140;

	//�g�����X�t�H�[���̍X�V
	LifeFrameTransform_.Update();
	LifeTransform_.Update();

}

/**
 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/30
 */
void LifeGage::PostRender()
{
	//�摜�̕`��
	LifeFrameImage_.Render();
	LifeImage_.Render();

	//���C�t�\���̕�������쐬
	char Now[10];
	sprintf_s(Now, "%d", *NowLife_);
	char Max[10];
	sprintf_s(Max, "%d", *MaxLife_);

	char str[30] = { 0 };
	strcat_s(str, "Life:");
	strcat_s(str, Now);
	strcat_s(str, "/");
	strcat_s(str, Max);

	//�t�H���g��`��
	Life_.Render(str,D3DXVECTOR2(10,500));

}