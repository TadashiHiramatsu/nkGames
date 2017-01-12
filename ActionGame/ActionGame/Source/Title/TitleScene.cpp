/**
 * @file Source\Title\TitleScene.cpp
 *
 * タイトルシーンクラスの実装.
 */
#include"stdafx.h"
#include"TitleScene.h"

//---------------------------------------------------------------------------------------------------
#include"HUD\TitleBack.h"
#include"GUI\TitleSystem.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//背景の作成
	TitleBack* titleback = NewGO<TitleBack>();

	//タイトルシステムの作成
	TitleSystem* titlesystem = NewGO<TitleSystem>();
	titlesystem->SetTitleBack(titleback);
}
