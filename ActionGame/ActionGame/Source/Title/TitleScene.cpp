/**
 * @file Source\Title\TitleScene.cpp
 *
 * �^�C�g���V�[���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleScene.h"

//---------------------------------------------------------------------------------------------------
#include"HUD\TitleBack.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//�w�i�̍쐬
	NewGO<TitleBack>();
}
