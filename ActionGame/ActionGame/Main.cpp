#include"stdafx.h"

#include"Game/GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdshow)
{
	SInitParam initparam;
	initparam.hInstance = hInstance;
	initparam.screenW = 900;
	initparam.screenH = 540;
	initparam.frameBufferW = 900*2;
	initparam.frameBufferH = 540*2;
	initparam.GameName = "アクションゲーム";
	Engine().Init(initparam);

	GameScene* gscene = new GameScene;
	SceneManager().ChangeScene(gscene);

	Engine().RunGameLoop();
}