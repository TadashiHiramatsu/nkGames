#include"stdafx.h"
#include"TestScene.h"

#include"UI\TestUI.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Start()
{
	NewGO<TestUI>();
}
