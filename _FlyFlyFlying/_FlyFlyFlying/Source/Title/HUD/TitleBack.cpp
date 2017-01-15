/**
 * @file Source\Title\HUD\TitleBack.cpp
 *
 * �^�C�g���o�b�N�N���X�̒�`.
 */
#include"stdafx.h"
#include"TitleBack.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
void TitleBack::Start()
{
	//�摜�̓ǂݍ���
	BackImage_.Load("Image/TitleBack.png");
	//�g�����X�t�H�[���̐ݒ�
	BackImage_.SetTransform(&BackRT_);

	//�傫�����X�N���[���T�C�Y�ɐݒ�
	BackRT_.Width_ = Engine().GetScreenW();
	BackRT_.Height_ = Engine().GetScreenH();

	//�A���J�[��ݒ�
	BackRT_.Anchor_ = RectTransform::MiddleCenter;

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
void TitleBack::Update()
{
	//�g�����X�t�H�[���̍X�V
	BackRT_.Update();
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/14
 */
void TitleBack::PostRender()
{
	//�w�i�摜�̕`��
	BackImage_.Render();
}
