#include"stdafx.h"
#include"TestUI.h"

TestUI::TestUI()
{
}

TestUI::~TestUI()
{
}

void TestUI::Start()
{
	imageP.Load("Image/Test.png");
	imageP.SetTransform(&rectTransformP); 

	rectTransformP.Anchor = RectTransform::AnchorPreset::TopRight;
	rectTransformP.Pivot = D3DXVECTOR2(1, 1);

	Mouse_x.Create(20, 20);
	Mouse_y.Create(20, 20);
	Image_x.Create(20, 20);
	Image_y.Create(20, 20);
}

void TestUI::Update()
{
	rectTransformP.Update();
}

void TestUI::Render()
{
	imageP.Render();

	Mouse_x.Render("マウスX", Input.GetMousePosX(), D3DXVECTOR2(0, 100));
	Mouse_y.Render("マウスY", Input.GetMousePosY(), D3DXVECTOR2(0, 120));
	Image_x.Render("画像Left", rectTransformP.ColRect.Left, D3DXVECTOR2(0, 160));
	Image_y.Render("画像Top", rectTransformP.ColRect.Top,D3DXVECTOR2(0, 180));
}
