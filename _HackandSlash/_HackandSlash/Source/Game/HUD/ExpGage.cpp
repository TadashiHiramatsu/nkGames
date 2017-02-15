/**
 * @file	Source\Game\GUI\ExpGage.cpp
 *
 * �o���l�Q�[�W�N���X�̎���.
 */
#include"stdafx.h"
#include"ExpGage.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
ExpGage::ExpGage()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
ExpGage::~ExpGage()
{
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::Start()
{
	//�t���[���̉摜�ǂݍ���
	ExpFrameImage_.Load("Image/ExpFrame.png");
	//�g�����X�t�H�[���̐ݒ�
	ExpFrameImage_.SetTransform(&ExpFrameTransform_);
	
	//�{�̂̉摜�ǂݍ���
	ExpImage_.Load("Image/Exp.png");
	//�g�����X�t�H�[���̐ݒ�
	ExpImage_.SetTransform(&ExpTransform_);

	//�ΐF�ɐݒ�
	ExpImage_.Color_.x = 0.0f;
	ExpImage_.Color_.z = 0.0f;

	//�e�q�֌W�ݒ�
	ExpTransform_.Parent_ = &ExpFrameTransform_;

	//�Q�[�W�̑傫����ݒ�
	ExpFrameTransform_.Width_ = 800;
	ExpFrameTransform_.Height_ = 20;
	ExpTransform_.Width_ = 750;
	ExpTransform_.Height_ = 10;

	//�t���[���̃A���J�[��������
	ExpFrameTransform_.Anchor_ = RectTransform::AnchorPresetE::BottomCenter;
	ExpFrameTransform_.Pivot_ = D3DXVECTOR2(0.5f, 0);

	//�{�̂̃A���J�[���t���[���̍�����
	ExpTransform_.Anchor_ = RectTransform::AnchorPresetE::MiddleLeft;
	ExpTransform_.Pivot_ = D3DXVECTOR2(0, 0.5f);
	//�������炷
	ExpTransform_.Position_.x = 25;

	//�o���l�̃|�C���^���擾
	NextExp_ = &Player_->GetParameter().NextLevelExperience_;
	NowExp_ = &Player_->GetParameter().Experience_;

	//���x���\���t�H���g�̍쐬
	Level_.Create(20, 20);
	Level_.SetTransform(&TextTransform_);
	TextTransform_.Parent_ = &ExpFrameTransform_;
	TextTransform_.Anchor_ = RectTransform::TopCenter;
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::Update()
{
	//�{�̂̑傫�����v�Z
	ExpTransform_.Width_ = min((float)*NowExp_ / (float)*NextExp_,1.0f) * 750;

	//�g�����X�t�H�[���̍X�V
	ExpFrameTransform_.Update();
	ExpTransform_.Update();

	TextTransform_.Update();

}

/**
 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 */
void ExpGage::PostRender()
{
	//�摜��`��
	ExpFrameImage_.Render();
	ExpImage_.Render();

	//���x���̃t�H���g���쐬
	char level[10];
	sprintf_s(level, "%d", Player_->GetParameter().Level_);

	//���S�n���擾
	int y = Engine().GetScreenH();
	int x = Engine().GetScreenW();
	x /= 2;

	//���x����`��
	Level_.Render(level);

}