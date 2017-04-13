/**
* �G�̑ҋ@��ԃN���X�̎���.
*/
#include"stdafx.h"
#include"EnemyState_Waiting.h"

#include"EnemyState_Stand.h"
#include"EnemyState_Loitering.h"

/**
* �R���X�g���N�^.
*
* @param enemy	�����̃|�C���^.
*/
EnemyState_Waiting::EnemyState_Waiting(IEnemy * enemy) :
	IEnemyState(enemy)
{
	LocalStateList_.push_back(new EnemyState_Stand(enemy));
	//LocalStateList_.push_back(new EnemyState_Loitering(enemy));
}

/**
* �J�n����.
* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
*/
void EnemyState_Waiting::Entry()
{
	IEnemyState::Entry();
	ChangeLocalState((int)LocalStateCodeE::Stand);
}

/**
* �X�V����.
* ���̏�Ԃ̎��ɖ��t���[�����s�����.
*/
void EnemyState_Waiting::Update()
{
	LocalStateList_[LocalState_]->Update();
}

/**
* �I������.
* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
*/
void EnemyState_Waiting::Exit()
{
	IEnemyState::Exit();
}
