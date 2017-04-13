/**
* �E�H�[���b�N�{�X�N���X��AI��
* ������ԃN���X�̎���.
*/
#include"stdafx.h"
#include"WarlockState_Stand.h"

/**
* �J�n����.
* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
*/
void WarlockState_Stand::Entry()
{
	IWarlockState::Entry();

	//���X�Ɋɂ߂�.
	float movespeed = Boss_->GetMoveSpeed();
	Boss_->SetMoveSpeed(movespeed * 0.8f);

	//�A�j���[�V������ύX.
	Boss_->PlayAnimation(Boss_Warlock::AnimationCodeE::Walk,0.3f);
}

/**
* �X�V����.
* ���̏�Ԃ̎��ɖ��t���[�����s�����.
*/
void WarlockState_Stand::Update()
{
	IWarlockState::Update();
	
	//���X�Ɋɂ߂�.
	float movespeed = Boss_->GetMoveSpeed();
	Boss_->SetMoveSpeed(movespeed * 0.8f);
}

/**
* �I������.
* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
*/
void WarlockState_Stand::Exit()
{
	IWarlockState::Exit();
}
