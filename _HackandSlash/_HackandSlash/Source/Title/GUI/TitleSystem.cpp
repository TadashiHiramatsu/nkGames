/**
 * @file Source\Title\GUI\TitleSystem.cpp
 *
 * �^�C�g���V�X�e���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleSystem.h"

#include"../../Game/GameScene.h"

 /**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::Start()
{
	//�w�i�쐬
	NewGO<TitleBack>(0);

	//�t�F�[�h�쐬
	Fade_ = NewGO<Fade>(2);

	//�^�C�g���l�[���摜�̏�����
	TitleNameImage_.Load("Image/NonTitle.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV������
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;
	
	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 150;
	TitleNameRT_.Position_ = Vector3(250, 200, 0);

	//�j���[�Q�[���摜�̏�����
	NewGameImage_.Load("Image/NewGame.png");
	NewGameImage_.SetTransform(&NewGameRT_);

	//�R���e�B�j���[�摜�̏�����
	ContinueImage_.Load("Image/Continue.png");
	ContinueImage_.SetTransform(&ContinueRT_);

	//������ݒ�
	NewGameRT_.Width_ = ContinueRT_.Width_ = 320;
	NewGameRT_.Height_ = ContinueRT_.Height_ = 80;

	//�ʒu��ݒ�
	NewGameRT_.Position_ = Vector3(300, -100,0);
	ContinueRT_.Position_ = Vector3(300, -200,0);

	//BGM�ǂݍ���.
	TitleBGM_ = NewGO<SoundSource>();
	TitleBGM_->InitStreaming("Title/TitleBGM");
	TitleBGM_->Play(true);

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::Update()
{
	switch (State_)
	{
	case TitleStateE::StartUp:
	{
		//RectUV���擾
		Vector4 rectUV = TitleNameImage_.RectUV_;

		//�N���^�C��
		static float StartTime = 2.0f;
		//�N�����[�J���^�C��
		static float StartUpLT = 0.0f;
		
		StartUpLT += Time().DeltaTime();
		if (StartUpLT >= StartTime)
		{
			//UV�����S�\���ɂ��炵�Ă���
			rectUV.x = fmax(0.0f, rectUV.x - 0.005f);
			rectUV.z = fmin(1.0f, rectUV.z + 0.005f);
			//�T�C�Y�𒲐�
			float a = 1 - rectUV.x * 2;
			TitleNameRT_.Width_ = 600 * a;
		}

		//RectUV��ݒ�
		TitleNameImage_.RectUV_ = rectUV;
		
		if (rectUV.x <= 0.0f)
		{
			//���S�ɕ\�����ꂽ�̂�Run��Ԃɕω�
			State_ = TitleStateE::Run;
			break;
		}
	}
	break;
	case TitleStateE::Run:
	{
		if (XInput().IsTrigger(ButtonE::A))
		{
			//A�{�^���������ꂽ.

			//�u���b�N�A�E�g��Ԃɕω�.
			State_ = TitleStateE::BlackOut;
			//�t�F�[�h�A�E�g�J�n.
			Fade_->StartFadeOut();

			//BGM�X�g�b�v.
			TitleBGM_->Stop();

			//���艹�Đ�.
			SoundSource* sound = NewGO<SoundSource>();
			sound->InitStreaming("Title/GameStart");
			sound->Play();

		}
	}
	break;
	case TitleStateE::BlackOut:
	{
		//�t�F�[�h�A�E�g�I��
		if (Fade_->GetState() == Fade::FadeCompletion)
		{
			//�Q�[���V�[���ɕύX
			SceneManager().ChangeScene<GameScene>();
			return;
		}
	}
	break;
	default:
		break;
	}

	//�g�����X�t�H�[���̍X�V
	TitleNameRT_.Update();
	NewGameRT_.Update();
	ContinueRT_.Update();
}

/**
 * �|�X�g�G�t�F�N�g��̕`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/12
 */
void TitleSystem::PostRender()
{
	TitleNameImage_.Render();
	NewGameImage_.Render();
	//ContinueImage_.Render();
}