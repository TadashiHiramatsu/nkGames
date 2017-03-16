/**
* �t�F�[�h�N���X�̎���.
*/
#include"stdafx.h"
#include"Fade.h"

/**
* ������.
*/
void Fade::Start()
{
	FadeImage_.Load("Image/FadeImage.png");
	FadeImage_.SetTransform(&FadeTransform_);

	//�傫�����t���X�N���[���ɐݒ�.
	FadeTransform_.Width_ = Engine().GetScreenW();
	FadeTransform_.Height_ = Engine().GetScreenH();

}

/**
* �X�V.
*/
void Fade::Update()
{
	switch (State_)
	{
	case FadeIn:
		if (FadeNowAlpha_ > 0)
		{
			//�t�F�[�h�����������ĂȂ��̂Œl���X�V.
			FadeNowAlpha_ -= FadeSpeed_ * Time().DeltaTime();
		}
		else
		{
			//�t�F�[�h������������.
			State_ = FadeCompletion;
		}
		break;
	case FadeOut:
		if (FadeNowAlpha_ < 1)
		{
			//�t�F�[�h�������肫���Ă��Ȃ��̂Œl���X�V.
			FadeNowAlpha_ += FadeSpeed_ * Time().DeltaTime();
		}
		else
		{
			//�t�F�[�h�������肫����.
			State_ = FadeCompletion;
		}
		break;
	case FadeCompletion:
		break;
	default:
		break;
	}

	//�g�����X�t�H�[���̍X�V
	FadeTransform_.Update();

	FadeImage_.Color_.w = FadeNowAlpha_;

}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void Fade::PostRender()
{
	FadeImage_.Render();
}
