/**
* �E�H�[���b�N�{�X�N���X��AI��
* ���S��ԃN���X�̒�`.
*/
#pragma once

#include"IWarlockState.h"

class WarlockState_Death : public IWarlockState
{
public:

	/**
	* �R���X�g���N�^.
	*/
	WarlockState_Death(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~WarlockState_Death()
	{
	}

	/**
	* �J�n����.
	* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
	*/
	void Entry();

	/**
	* �X�V����.
	* ���̏�Ԃ̎��ɖ��t���[�����s�����.
	*/
	void Update();

	/**
	* �I������.
	* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
	*/
	void Exit();

private:

};