/**
* �E�H�[���b�N�{�X�N���X��AI��
* �Ǐ]��ԃN���X�̒�`.
*/
#pragma once

#include"IWarlockState.h"

/**
* �E�H�[���b�N�{�X�N���X��AI��
* �Ǐ]��ԃN���X.
*/
class WarlockState_Chase : public IWarlockState
{
public:

	/**
	* �R���X�g���N�^.
	*/
	WarlockState_Chase(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~WarlockState_Chase()
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