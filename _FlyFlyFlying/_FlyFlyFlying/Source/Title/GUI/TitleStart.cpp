/**
 * @file Source\Title\GUI\TitleStart.cpp
 *
 * �^�C�g���X�^�[�g�N���X�̒�`.
 */
#include"stdafx.h"
#include"TitleStart.h"

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::Start()
{
	//�摜�ǂݍ���
	StartImage_.Load("Image/Start.png");
	//�g�����X�t�H�[���̐ݒ�
	StartImage_.SetTransform(&StartRT_);

	//�傫������
	StartRT_.Width_ = 200;
	StartRT_.Height_ = 100;
	
	//�ʒu����
	StartRT_.Position_ = D3DXVECTOR2(0, -100);

	//�A���J�[�ݒ�
	StartRT_.Anchor_ = RectTransform::MiddleCenter;
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::Update()
{
	StartRT_.Update();
}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/15
 */
void TitleStart::PostRender()
{
	StartImage_.Render();
}