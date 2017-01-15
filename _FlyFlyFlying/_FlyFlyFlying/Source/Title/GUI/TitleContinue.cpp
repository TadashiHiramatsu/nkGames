/**
 * @file Source\Title\GUI\TitleContinue.cpp
 *
 * �^�C�g���R���e�B�j���[�N���X�̎���.
 */
#include"stdafx.h"
#include"TitleContinue.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::Start()
{
	ContinueImage_.Load("Image/Continue.png");
	ContinueImage_.SetTransform(&ContinueRT_);

	ContinueRT_.Width_ = 180;
	ContinueRT_.Height_ = 80;

	ContinueRT_.Position_ = D3DXVECTOR2(0, -200);

	ContinueRT_.Anchor_ = RectTransform::MiddleCenter;

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::Update()
{
	ContinueRT_.Update();
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleContinue::PostRender()
{
	ContinueImage_.Render();
}
