/**
 * @file Source\Title\TitleScene.cpp
 *
 * �^�C�g���V�[���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleScene.h"

//---------------------------------------------------------------------------------------------------
#include"HUD\TitleBack.h"
#include"GUI\TitleSystem.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//�w�i�̍쐬
	TitleBack* titleback = NewGO<TitleBack>();

	//�^�C�g���V�X�e���̍쐬
	TitleSystem* titlesystem = NewGO<TitleSystem>();
	titlesystem->SetTitleBack(titleback);
}
