/**
* �^�C�g���Z���N�g�̃R���e�B�j���[�N���X�̒�`.
*/
#include"stdafx.h"
#include"TitleSelect_Continue.h"

#include"..\..\..\Game\GameScene.h"

/**
* ������.
*/
void TitleSelect_Continue::Start()
{
	//�j���[�Q�[���摜�̏�����
	SelectImage_.Load("Image/continue.png");
	ITitleSelect::Start();

	//�ʒu�ݒ�.
	SelectRT_.Position_ = Vector3(300, -150, 0);

	//�傫����ݒ�.
	SelectRT_.Width_ = 374 /2;
}

/**
* �X�V.
*/
void TitleSelect_Continue::Update()
{
	ITitleSelect::Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void TitleSelect_Continue::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* �I�����ꂽ��.
*/
bool TitleSelect_Continue::OnTrigger()
{
	return false;

	//�Q�[���V�[���Ɉڍs.
	SceneManager().ChangeScene<GameScene>();

	return true;
}
