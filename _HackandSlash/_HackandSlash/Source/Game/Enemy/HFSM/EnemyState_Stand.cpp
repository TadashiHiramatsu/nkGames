/**
* �G�̗�����ԃN���X�̎���.
*/
#include"stdafx.h"
#include"EnemyState_Stand.h"

/**
* �J�n����.
* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
*/
void EnemyState_Stand::Entry()
{

}

/**
* �X�V����.
* ���̏�Ԃ̎��ɖ��t���[�����s�����.
*/
void EnemyState_Stand::Update()
{
	//�ړ����x.
	float speed = Enemy_->GetMoveSpeed();

	//���X�Ɏ~�܂�.
	speed *= 0.8f;

	//�ړ����x��ݒ�.
	Enemy_->SetMoveSpeed(speed);
}

/**
* �I������.
* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
*/
void EnemyState_Stand::Exit()
{

}
