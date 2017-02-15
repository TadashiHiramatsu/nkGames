#include"stdafx.h"
#include"MenuBar.h"


void MenuBar::Start()
{

	BarImage_.Load("Image/Test.png");
	BarImage_.SetTransform(&BarTransform_);

	BarTransform_.Height_ = 50;
	BarTransform_.Width_ = 900;

	BarTransform_.Position_.y = 280; 
	BarTransform_.Position_.z = 1;

}

void MenuBar::Update()
{
	BarTransform_.Update();
}

void MenuBar::Render()
{
	BarImage_.Render();
}
