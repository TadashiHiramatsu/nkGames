/**
* �^�C�g���V�[���̃Z���N�g�̊��N���X�̎���.
*/
#include"stdafx.h"
#include"ITitleSelect.h"

/**
* ������.
*/
void ITitleSelect::Start()
{
	//�g�����X�t�H�[���̐ݒ�.
	SelectImage_.SetTransform(&SelectRT_);

	SelectRT_.Height_ = 73 / 2;
}

/**
* �X�V.
*/
void ITitleSelect::Update()
{
	//�g�����X�t�H�[���̍X�V.
	SelectRT_.Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void ITitleSelect::PostRender()
{
	//�摜�̕`��.
	SelectImage_.Render();
}
