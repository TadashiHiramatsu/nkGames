#include"stdafx.h"

#include"Game/GameScene.h"

#include"Test/TestScene.h"

void InitEngine(HINSTANCE _hInstance)
{
	SInitParam initparam;
	initparam.hInstance = _hInstance;
	initparam.screenW = 1200;
	initparam.screenH = 675;
	initparam.frameBufferW = initparam.screenW * 1;
	initparam.frameBufferH = initparam.screenH * 1;
	initparam.GameName = "アクションゲーム";
	initparam.isCenter = false;
	Engine().Init(initparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	InitEngine(hInstance);

	SceneManager().ChangeScene<GameScene>();
	//SceneManager().ChangeScene<TestScene>();

	Engine().RunGameLoop();
}