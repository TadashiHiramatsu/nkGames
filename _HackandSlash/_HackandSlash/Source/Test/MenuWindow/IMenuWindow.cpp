#include"stdafx.h"
#include"IMenuWindow.h"

void IMenuWindow::NameStart(RectTransform* parent, const char * filepath, float pos)
{
	NameImage_.Load(filepath);
	NameImage_.SetTransform(&NameTransform_);
	NameTransform_.Parent_ = parent;
	NameTransform_.Anchor_ = RectTransform::MiddleLeft;
	NameTransform_.Position_.x = pos;

	NameTransform_.Height_ = 30;
	NameTransform_.Width_ = 90;
}
