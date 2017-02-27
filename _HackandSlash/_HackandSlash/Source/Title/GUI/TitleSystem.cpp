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
	TitleBack_ = NewGO<TitleBack>(0);

	//�^�C�g���l�[���摜�̏�����
	TitleNameImage_.Load("Image/NonTitle.png");
	TitleNameImage_.SetTransform(&TitleNameRT_);

	//UV������
	TitleNameImage_.RectUV_.x = 0.5;
	TitleNameImage_.RectUV_.z = 0.5;
	
	TitleNameRT_.Width_ = 0;
	TitleNameRT_.Height_ = 150;
	TitleNameRT_.Position_ = D3DXVECTOR3(250, 200, 0);

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
	NewGameRT_.Position_ = D3DXVECTOR3(300, -100,0);
	ContinueRT_.Position_ = D3DXVECTOR3(300, -200,0);

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
	case TitleSystem::StartUp:
	{
		//RectUV���擾
		D3DXVECTOR4 rectUV = TitleNameImage_.RectUV_;

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
			State_ = Run;
			break;
		}
	}
	break;
	case TitleSystem::Run:
	{
		if (XInput().IsTrigger(ButtonE::ButtonA))
		{
			//�G���^�[�L�[�������ꂽ
			State_ = BlackOut;
		}
	}
	break;
	case TitleSystem::BlackOut:
	{
		//���X�ɈÂ�
		BlackOutColor_ = fmax(0.0f, BlackOutColor_ - 0.01f);

		//�F���쐬
		D3DXVECTOR4 color = D3DXVECTOR4(BlackOutColor_, BlackOutColor_, BlackOutColor_, 1.0f);
		TitleNameImage_.Color_ = color;
		NewGameImage_.Color_ = color;
		ContinueImage_.Color_ = color;
		TitleBack_->SetColor(color);

		//�u���b�N�A�E�g�I��
		if (BlackOutColor_ <= 0.0f)
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