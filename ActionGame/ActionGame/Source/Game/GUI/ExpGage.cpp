/**
 * @file	Source\Game\GUI\ExpGage.cpp
 *
 * Implements the exponent gage class.
 */
#include"stdafx.h"
#include"ExpGage.h"

ExpGage::ExpGage()
{
}

ExpGage::~ExpGage()
{
}

void ExpGage::Start()
{
	ExpFrameImage.Load("Image/ExpFrame.png");
	ExpFrameImage.SetTransform(&ExpFrameTransform);

	ExpImage.Load("Image/Exp.png");
	ExpImage.SetTransform(&ExpTransform);

	//eŽqŠÖŒWÝ’è
	ExpTransform.Parent = &ExpFrameTransform;

	ExpFrameTransform.Width = 800;
	ExpFrameTransform.Height = 20;
	ExpTransform.Width = 750;
	ExpTransform.Height = 10;

	ExpFrameTransform.Anchor = RectTransform::AnchorPreset::BottomCenter;
	ExpFrameTransform.Pivot = D3DXVECTOR2(0.5f, 0);

	ExpTransform.Anchor = RectTransform::AnchorPreset::MiddleLeft;
	ExpTransform.Pivot = D3DXVECTOR2(0, 0.5f);
	ExpTransform.Position.x = 25;

	NextExp = &player->GetPlayerParameter().NextLevelExperience;
	NowExp = &player->GetPlayerParameter().Experience;

	Level.Create(20, 20);
}

void ExpGage::Update()
{
	ExpTransform.Width = min((float)*NowExp / (float)*NextExp,1.0f) * 750;

	ExpFrameTransform.Update();
	ExpTransform.Update();
}

void ExpGage::Render()
{
	ExpFrameImage.Render();
	ExpImage.Render();

	char level[10];
	sprintf_s(level, "%d", player->GetPlayerParameter().Level);

	int y = Engine().GetScreenH();
	int x = Engine().GetScreenW();
	x /= 2;

	Level.Render(level, D3DXVECTOR2(x - 10,y - 20));
}
