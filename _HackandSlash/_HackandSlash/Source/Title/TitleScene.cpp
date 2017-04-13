/**
 * @file Source\Title\TitleScene.cpp
 *
 * タイトルシーンクラスの実装.
 */
#include"stdafx.h"
#include"TitleScene.h"

/*------------------------------------------------------------------------------------------------------------*/

#include"TitleSystem.h"

/**
 * 初期化.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleScene::Start()
{
	//タイトルシステムの作成
	NewGO<TitleSystem>(1);

}
