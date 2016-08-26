#include"stdafx.h"
#include"CTitleScene.h"

void CTitleScene::Init()
{
	title.Load("Texture/TitleBack.jpg");
	title.Init();
}

void CTitleScene::Update()
{
	title.Update(D3DXVECTOR3(Engine().GetFrameW() / 2, Engine().GetFrameH() / 2, 0), D3DXVECTOR3(Engine().GetFrameW(), Engine().GetFrameH(), 0));
}

void CTitleScene::Render()
{
	title.Render();
}

void CTitleScene::Release()
{
}
