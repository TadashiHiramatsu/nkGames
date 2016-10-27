#include"stdafx.h"
#include"GameScene.h"

#include"GameCamera.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	Player.Init();
	Monster.Init();
	Ground.Init();
	Skybox.Init();
	MainCamera.Init();
}

void GameScene::Update()
{
	Player.Update();
	Monster.Update();
	Ground.Update();
	Skybox.SetPosition(Player.GetPos());
	Skybox.Update();
	MainCamera.Update();
}

void GameScene::Render()
{
	Player.Render();
	Monster.Render();
	Ground.Render();
	Skybox.Render();
}

void GameScene::Release()
{
	Player.Release();
	Monster.Release();
	Ground.Release();
	Skybox.Release();
	MainCamera.Release();
}
