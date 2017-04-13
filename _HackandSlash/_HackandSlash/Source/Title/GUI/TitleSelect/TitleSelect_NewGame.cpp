/**
* �^�C�g���Z���N�g�̃j���[�Q�[���N���X�̎���.
*/
#include"stdafx.h"
#include"TitleSelect_NewGame.h"

#include"..\..\..\Game\GameScene.h"

/**
* ������.
*/
void TitleSelect_NewGame::Start()
{
	//�j���[�Q�[���摜�̏�����
	SelectImage_.Load("Image/new_game.png");
	ITitleSelect::Start();

	//�ʒu�ݒ�.
	SelectRT_.Position_ = Vector3(300, -100, 0);

	//�傫����ݒ�.
	SelectRT_.Width_ = 464 / 2;
}

/**
* �X�V.
*/
void TitleSelect_NewGame::Update()
{
	ITitleSelect::Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void TitleSelect_NewGame::PostRender()
{
	ITitleSelect::PostRender();
}

/**
* �I�����ꂽ��.
*/
bool TitleSelect_NewGame::OnTrigger()
{
	//�Q�[���V�[���Ɉڍs.
	SceneManager().ChangeScene<GameScene>();

	return true;
}
