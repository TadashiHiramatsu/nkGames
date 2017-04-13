/**
 * @file Source\Title\GUI\TitleSystem.cpp
 *
 * �^�C�g���V�X�e���N���X�̎���.
 */
#include"stdafx.h"
#include"TitleSystem.h"

#include"GUI\TitleSelect\TitleSelect_NewGame.h"
#include"GUI\TitleSelect\TitleSelect_Continue.h"
#include"GUI\TitleSelect\TitleSelect_Exit.h"

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

	TitleName_ = NewGO<TitleName>();

	//�t�F�[�h�쐬
	Fade_ = NewGO<Fade>(2);
	Fade_->StartFadeIn();

	InitSelect();

	CursorImage_.Load("Image/SelectCursor.png");
	CursorImage_.SetTransform(&CursorRT_);

	CursorRT_.Width_ = 69 / 2.5f;
	CursorRT_.Height_ = 71 / 2.5f;
	CursorRT_.Pivot_ = Vector2(1, 0.5f);
	CursorRT_.Anchor_ = AnchorPresetE::MiddleLeft;
	CursorRT_.Position_.x = -10;

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
	if (TitleName_->IsFade())
	{
		//�Q�[�����\���̃t�F�[�h���I��.

		if (!isDecision_)
		{
			//�����ԂłȂ�.

			if (CursorUpDownMove())
			{
				CursorRT_.Parent_ = &SelectList_[NowSelect_]->GetRectTransform();

				//�J�[�\�����Đ�.
				SoundSource* sound = NewGO<SoundSource>();
				sound->InitOnMemory("Common/SelectChange");
				sound->Play();
			}

			if (XInput().IsTrigger(ButtonE::A))
			{
				//A�{�^���������ꂽ.

				isDecision_ = true;

				//���艹�Đ�.
				SoundSource* sound = NewGO<SoundSource>();
				sound->InitStreaming("Title/GameStart");
				sound->Play();

				//BGM�X�g�b�v.
				TitleBGM_->Stop();

				//�t�F�[�h�A�E�g�J�n.
				Fade_->StartFadeOut();
			}
		}
		else
		{
			//������.

			if (Fade_->GetState() == Fade::FadeStateE::FadeCompletion)
			{
				//�t�F�[�h���I�������̂ŃZ���N�g���e�����s. 
				bool is = SelectList_[(int)NowSelect_]->OnTrigger();
				if (!is)
				{
					isDecision_ = false;
					Fade_->StartFadeIn();
					TitleBGM_->Play(true);
				}
			}
		}
	}

	CursorRT_.Update();
}

/**
* �|�X�g�G�t�F�N�g��̕`��.
*/
void TitleSystem::PostRender()
{
	CursorImage_.Render();
}

/**
* �Z���N�g�̏�����.
*/
void TitleSystem::InitSelect()
{
	//�j���[�Q�[��
	SelectList_[(int)SelectStateE::NewGame] = NewGO<TitleSelect_NewGame>();
	//�R���e�B�j���[
	SelectList_[(int)SelectStateE::Continue] = NewGO<TitleSelect_Continue>();
	//�G�O�W�b�g
	SelectList_[(int)SelectStateE::Exit] = NewGO<TitleSelect_Exit>();

	NowSelect_ = (int)SelectStateE::NewGame;

	CursorRT_.Parent_ = &SelectList_[NowSelect_]->GetRectTransform();
}

/**
* �J�[�\���̏㉺�ړ�.
*/
bool TitleSystem::CursorUpDownMove()
{
	//�A�łł��Ȃ��悤�ɂ���.
	static bool isTrigger = false;

	if (!isTrigger)
	{
		//�O�t���[���ɉ�����Ă��Ȃ�.

		if (XInput().GetLeftStick().y >= 0.1f)
		{
			//��Ɉړ�.
			if (NowSelect_ == (int)SelectStateE::StateBegin)
			{
				NowSelect_ = (int)SelectStateE::StateEnd;
			}
			else
			{
				NowSelect_--;
			}
			isTrigger = true;

			return true;
		}
		if (XInput().GetLeftStick().y <= -0.1f)
		{
			//���Ɉړ�.
			if (NowSelect_ == (int)SelectStateE::StateEnd)
			{
				NowSelect_ = (int)SelectStateE::StateBegin;
			}
			else
			{
				NowSelect_++;
			}
			isTrigger = true;

			return true;
		}
	}
	else
	{
		if (XInput().GetLeftStickAngle() <= 0.0f)
		{
			isTrigger = false;
		}
	}

	return false;
}
