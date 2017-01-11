/**
 * @file Source\Title\HUD\TitleBack.cpp
 *
 * �^�C�g���o�b�N�N���X�̎���.
 */
#include"stdafx.h"
#include"TitleBack.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
TitleBack::TitleBack()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
TitleBack::~TitleBack()
{
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::Start()
{
	BackImage_.Load("Image/TitleBack.jpg");
	BackImage_.SetTransform(&BackRT_);

	BackRT_.Width_ = Engine().GetScreenW();
	BackRT_.Height_ = Engine().GetScreenH();

	BackRT_.Anchor_ = RectTransform::MiddleCenter;
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::Update()
{
	//�g�����X�t�H�[���̍X�V
	BackRT_.Update();
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void TitleBack::PostRender()
{
	//�w�i�摜�̕`��
	BackImage_.Render();
}