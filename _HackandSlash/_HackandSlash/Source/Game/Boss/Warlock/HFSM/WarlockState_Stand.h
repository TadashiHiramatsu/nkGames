/**
* �E�H�[���b�N�{�X�N���X��AI��
* ������ԃN���X�̒�`.
*/
#pragma once

#include"IWarlockState.h"

/**
* �E�H�[���b�N�{�X�N���X��AI��
* ������ԃN���X.
*/
class WarlockState_Stand : public IWarlockState
{
public:

	/**
	* �R���X�g���N�^.
	*/
	WarlockState_Stand(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~WarlockState_Stand()
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