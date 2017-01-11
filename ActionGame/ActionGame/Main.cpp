/**
 * @file Main.cpp
 *
 * WinMainプログラムの実装.
 */
#include"stdafx.h"

#include"Game/GameScene.h"
#include"Title/TitleScene.h"

/**
 * エンジンの初期化関数.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param hInstance The instance.
 */
void InitEngine(HINSTANCE hInstance)
{
	InitParamS initparam;
	initparam.hInstance_ = hInstance;
	initparam.ScreenBufferW_ = 1200;
	initparam.ScreenBufferH_ = 675;
	initparam.FrameBufferW_ = initparam.ScreenBufferW_ * 2;
	initparam.FrameBufferH_ = initparam.ScreenBufferH_ * 2;
	initparam.GameName_ = "Hack and Slash";
	initparam.isCenter_ = false;
	Engine().Init(initparam);
}

/**
 * WindowMain関数.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/10
 *
 * @param hInstance	    The instance.
 * @param hPrevInstance The previous instance.
 * @param lpCmdLine	    The command line.
 * @param nCmdshow	    The cmdshow.
 *
 * @return A WINAPI.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	InitEngine(hInstance);

	//SceneManager().ChangeScene<GameScene>();

	SceneManager().ChangeScene<TitleScene>();

	Engine().RunGameLoop();
}