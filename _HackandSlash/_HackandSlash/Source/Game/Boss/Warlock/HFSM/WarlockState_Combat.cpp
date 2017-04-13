/**
* �E�H�[���b�N�{�X�N���X��AI��
* �퓬��ԃN���X�̎���.
*/
#include"stdafx.h"
#include"WarlockState_Combat.h"

#include"WarlockState_Stand.h"
#include"WarlockState_Chase.h"
#include"WarlockState_Turn.h"
#include"WarlockState_Attack.h"
#include"WarlockState_Damage.h"

/**
* �J�n����.
* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
*/
void WarlockState_Combat::Entry()
{
	IWarlockState::Entry();

	ChangeLocalState((int)LocalStateCodeE::Stand);
}

/**
* �X�V����.
* ���̏�Ԃ̎��ɖ��t���[�����s�����.
*/
void WarlockState_Combat::Update()
{
	IWarlockState::Update();

	LocalStateList_[LocalState_]->Update();

	//�ړI�n�܂ł̕����x�N�g�����擾
	Vector3 playerPos = Boss_->GetPlayerPosition();

	Vector3 toPlayer;
	toPlayer.Sub(playerPos, Boss_->Transform_.Position_);

	//�ړ�������ݒ�
	MoveDirection_ = Vector3(toPlayer.x, 0, toPlayer.z);

	//�����Ă�������ɉ�]
	Boss_->Transform_.Rotation_.RotationAxis(Vector3::Up, D3DXToDegree(atan2f(MoveDirection_.x, MoveDirection_.z)) + 180.0f);

}

/**
* �I������.
* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
*/
void WarlockState_Combat::Exit()
{
	IWarlockState::Exit();
}

/**
* ���[�J���̏�Ԃ�������.
*/
void WarlockState_Combat::InitLocalState()
{
	//�������.
	LocalStateList_.push_back(unique_ptr<WarlockState_Stand>(new WarlockState_Stand(Boss_)));
	//�Ǐ]���.
	LocalStateList_.push_back(unique_ptr<WarlockState_Chase>(new WarlockState_Chase(Boss_)));
	//��]���.
	LocalStateList_.push_back(unique_ptr<WarlockState_Turn>(new WarlockState_Turn(Boss_)));
	//�U�����.
	LocalStateList_.push_back(unique_ptr<WarlockState_Attack>(new WarlockState_Attack(Boss_)));
	//�_���[�W���.
	LocalStateList_.push_back(unique_ptr<WarlockState_Damage>(new WarlockState_Damage(Boss_)));

	
}
