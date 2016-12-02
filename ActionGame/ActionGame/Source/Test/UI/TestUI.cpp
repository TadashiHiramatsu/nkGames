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
	image.Load("Image/Test.png");
	image.SetTransform(&rectTransform);
	imageC.Load("Image/Test.png");
	imageC.SetTransform(&rectTransformC);

	rectTransformP.Anchor = RectTransform::AnchorPreset::MiddleCenter;
	rectTransformP.Pivot = D3DXVECTOR2(0.5f, 0.5f);

	rectTransform.Parent = &rectTransformP;
	rectTransform.Anchor = RectTransform::AnchorPreset::MiddleRight;
	rectTransform.Scale = D3DXVECTOR2(0.5, 0.5);
	rectTransform.Pivot = D3DXVECTOR2(0, 0.5);
	rectTransform.Position = D3DXVECTOR2(200, 0);

	rectTransformC.Parent = &rectTransform;
	rectTransformC.Anchor = RectTransform::AnchorPreset::MiddleRight;
	rectTransformC.Scale = D3DXVECTOR2(0.5, 0.5);
	rectTransformC.Pivot = D3DXVECTOR2(0, 0.5);
	rectTransformC.Position = D3DXVECTOR2(50, 0);
}

void TestUI::Update()
{
	static float z = 0;
	z++;
	rectTransformP.RotationZ(z);
	rectTransform.RotationZ(z);
	rectTransformC.RotationZ(z);

	rectTransformP.Update();
	rectTransform.Update();
	rectTransformC.Update();
}

void TestUI::Render()
{
	imageP.Render();
	image.Render();
	imageC.Render();
}
