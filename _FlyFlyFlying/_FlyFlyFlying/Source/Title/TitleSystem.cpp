/**
 * @file Source\Title\TitleSystem.cpp
 *
 * �^�C�g���V�X�e���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleSystem.h"

void TitleSystem::Start()
{

	NewGO<TitleBack>(1);
	NewGO<TitleStart>(1);
	NewGO<TitleContinue>(1);

}

void TitleSystem::Update()
{
}
