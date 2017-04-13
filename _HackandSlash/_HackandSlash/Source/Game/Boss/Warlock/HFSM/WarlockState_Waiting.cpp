/**
* �E�H�[���b�N�{�X�N���X��AI��
* �ҋ@��ԃN���X�̎���.
*/
#include"stdafx.h"
#include"WarlockState_Waiting.h"

/**
* �J�n����.
* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
*/
void WarlockState_Waiting::Entry()
{
	IWarlockState::Entry();

	//�ړ����x������.
	Boss_->SetMoveSpeed(0.0f);
	Boss_->PlayAnimation(Boss_Warlock::AnimationCodeE::Idol,0.3f);
}

/**
* �X�V����.
* ���̏�Ԃ̎��ɖ��t���[�����s�����.
*/
void WarlockState_Waiting::Update()
{
	IWarlockState::Update();

	Vector3 playerPos = Boss_->GetPlayerPosition();

	Vector3 toPlayer;
	toPlayer.Sub(playerPos, Boss_->Transform_.Position_);

	//�v���C���[�Ƃ̋���.
	float toPlayerLen = toPlayer.Length();

	if (toPlayerLen < PlayerDiscovery_)
	{
		Boss_->ChangeState(Boss_Warlock::StateCodeE::Combat);
	}

}

/**
* �I������.
* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
*/
void WarlockState_Waiting::Exit()
{
	IWarlockState::Exit();
}
