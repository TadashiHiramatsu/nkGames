/**
 * @file Source\Title\TitleSystem.cpp
 *
 * タイトルシステムクラスの実装.
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
