/**
* �G�̗�����ԃN���X�̒�`.
*/
#pragma once

#include"IEnemyState.h"

/**
* �G�̗�����ԃN���X.
*/
class EnemyState_Stand : public IEnemyState 
{
public:

	/**
	* �R���X�g���N�^.
	*
	* @param enemy �����̃|�C���^.
	*/
	EnemyState_Stand(IEnemy* enemy) :
		IEnemyState(enemy)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~EnemyState_Stand()
	{
	}

	/**
	* �J�n����.
	* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
	*/
	void Entry()override;

	/**
	* �X�V����.
	* ���̏�Ԃ̎��ɖ��t���[�����s�����.
	*/
	void Update()override;

	/**
	* �I������.
	* ���̏�Ԃ���J�ڂ����Ƃ��Ɏ��s�����.
	*/
	void Exit()override;

private:

	/** �����~�܂鎞��. */
	float StandTime_ = 1.0f;
	/** �����~�܂鎞�Ԍv���̂��߂̃��[�J���^�C��. */
	float StandLocalTime_ = 0.0f;

};