/**
 * @file Source\Title\TitleScene.cpp
 *
 * タイトルシーンクラスの実装.
 */
#include"stdafx.h"
#include"TitleScene.h"

//---------------------------------------------------------------------------------------------------
#include"HUD\TitleBack.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//背景の作成
	NewGO<TitleBack>();
}
