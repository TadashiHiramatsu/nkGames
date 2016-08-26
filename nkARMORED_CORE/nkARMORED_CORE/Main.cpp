#include"stdafx.h"
#include"Source\GameScene\CGameScene.h"
#include"Source\TitleScene\CTitleScene.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdshow)
{
	SInitParam initparam;
	initparam.hInstance = hInstance;
	initparam.screenW = 900;
	initparam.screenH = 540;
	initparam.frameBufferW = 900*3;
	initparam.frameBufferH = 540*3;
	initparam.GameName = "ARMORED_CORE";

	Engine().Init(initparam);

	CGameScene* game = new CGameScene();
	SceneManager().ChangeScene(game);

	//CTitleScene* title = new CTitleScene();
	//SceneManager().ChangeScene(title);


	Engine().RunGameLoop();
}