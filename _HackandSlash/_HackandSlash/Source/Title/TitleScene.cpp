/**
 * @file Source\Title\TitleScene.cpp
 *
 * �^�C�g���V�[���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleScene.h"

/*------------------------------------------------------------------------------------------------------------*/

#include"TitleSystem.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//�^�C�g���V�X�e���̍쐬
	NewGO<TitleSystem>(1);

}
