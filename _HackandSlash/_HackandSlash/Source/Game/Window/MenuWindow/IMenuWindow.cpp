/**
* ���j���[�E�B���h�E�̊��N���X�̎���.
*/
#include"stdafx.h"
#include"IMenuWindow.h"

/**
* �\�����̏�����.
*/
void IMenuWindow::NameStart(RectTransform* parent, const char * filepath, float pos, float width)
{
	NameImage_.Load(filepath);
	NameImage_.SetTransform(&NameTransform_);
	NameTransform_.Parent_ = parent;
	NameTransform_.Anchor_ = AnchorPresetE::MiddleLeft;
	NameTransform_.Position_.x = pos;

	NameTransform_.Height_ = 90 / 3;
	NameTransform_.Width_ = width / 3;
}
