/**
 * @file Main.cpp
 *
 * WinMainプログラムの実装.
 */
#include"stdafx.h"

/*----------------------------------------------------------------------------------------------------------*/
#include"Source\Title\TitleScene.h"

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
	initparam.GameName_ = "FlyFlyFlying";
	initparam.isCenter_ = false;
	Engine().Init(initparam);
}

/**
* WindowMain関数.
*
* @author HiramatsuTadashi
* @date 2017/01/10
*
* @param hInstance	    インスタンスハンドル.
* @param hPrevInstance The previous instance.
* @param lpCmdLine	    コマンドライン.
* @param nCmdshow	    コマンドショー.
*
* @return A WINAPI.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	//エンジンの初期化
	InitEngine(hInstance);

	SceneManager().ChangeScene<TitleScene>();

	//エンジン起動!!
	Engine().RunGameLoop();
}