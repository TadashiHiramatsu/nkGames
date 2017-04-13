/**
* �^�C�g���V�[���̃Q�[���^�C�g���\���N���X�̎���.
*/
#include"stdafx.h"
#include"TitleName.h"

/**
* ������.
*/
void TitleName::Start()
{
	//�^�C�g���l�[���摜�̏�����
	TitleNameImage_.Load("Image/non_title.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV������
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;

	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 73 * 1.5;
	TitleNameRT_.Position_ = Vector3(250, 200, 0);

	//�t�F�[�h���x�̐ݒ�.
	FadeSpeed = 3.0f;
}

/**
* �X�V.
*/
void TitleName::Update()
{
	if (!isFade_)
	{
		//RectUV���擾
		Vector4 rectUV = TitleNameImage_.RectUV_;

		//�N���^�C��
		static float StartTime = 2.0f;
		//�N�����[�J���^�C��
		static float StartLT = 0.0f;

		StartLT += Time().DeltaTime();
		if (StartLT >= StartTime)
		{
			//UV�����S�\���ɂ��炵�Ă���

			//2�b�����ĕ\������.
			float speed = 1 / FadeSpeed * Time().DeltaTime();

			rectUV.x = fmax(0.0f, rectUV.x - speed);
			rectUV.z = fmin(1.0f, rectUV.z + speed);

			//�T�C�Y�𒲐�
			float a = 1 - rectUV.x * 2;
			TitleNameRT_.Width_ = 396 * 1.5 * a;
		}

		//RectUV��ݒ�
		TitleNameImage_.RectUV_ = rectUV;

		if (rectUV.x <= 0.0001f)
		{
			isFade_ = true;
		}
	}

	//�g�����X�t�H�[���̍X�V.
	TitleNameRT_.Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void TitleName::PostRender()
{
	TitleNameImage_.Render();
}
