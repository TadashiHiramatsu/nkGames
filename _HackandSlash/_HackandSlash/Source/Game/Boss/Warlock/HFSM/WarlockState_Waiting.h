/**
* �E�H�[���b�N�{�X�N���X��AI��
* �ҋ@��ԃN���X�̒�`.
*/
#pragma once

#include"IWarlockState.h"

class WarlockState_Waiting : public IWarlockState
{
public:

	/**
	* �R���X�g���N�^.
	*/
	WarlockState_Waiting(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~WarlockState_Waiting()
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

	/** �v���C���[�𔭌����鋗��. */
	float PlayerDiscovery_ = 30.0f;

};