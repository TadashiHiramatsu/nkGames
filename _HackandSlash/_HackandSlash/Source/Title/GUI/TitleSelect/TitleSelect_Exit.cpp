/**
* �^�C�g���Z���N�g�̃G�O�W�b�g�N���X�̒�`.
*/
#include"stdafx.h"
#include"TitleSelect_Exit.h"

/**
* ������.
*/
void TitleSelect_Exit::Start()
{
	//�j���[�Q�[���摜�̏�����
	SelectImage_.Load("Image/exit.png");
	ITitleSelect::Start();

	//�ʒu�ݒ�.
	SelectRT_.Position_ = Vector3(300, -200, 0);

	//�傫����ݒ�.
	SelectRT_.Width_ = 173 / 2;
}

/**
* �X�V.
*/
void TitleSelect_Exit::Update()
{
	ITitleSelect::Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void TitleSelect_Exit::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* �I�����ꂽ��.
*/
bool TitleSelect_Exit::OnTrigger()
{
	Engine().GameExit();

	return true;
}
