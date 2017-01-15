/**
 * @file Main.cpp
 *
 * WinMain�v���O�����̎���.
 */
#include"stdafx.h"

/*----------------------------------------------------------------------------------------------------------*/
#include"Source\Title\TitleScene.h"

 /**
 * �G���W���̏������֐�.
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
* WindowMain�֐�.
*
* @author HiramatsuTadashi
* @date 2017/01/10
*
* @param hInstance	    �C���X�^���X�n���h��.
* @param hPrevInstance The previous instance.
* @param lpCmdLine	    �R�}���h���C��.
* @param nCmdshow	    �R�}���h�V���[.
*
* @return A WINAPI.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	//�G���W���̏�����
	InitEngine(hInstance);

	SceneManager().ChangeScene<TitleScene>();

	//�G���W���N��!!
	Engine().RunGameLoop();
}