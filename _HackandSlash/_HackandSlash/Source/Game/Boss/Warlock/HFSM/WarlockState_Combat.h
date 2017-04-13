/**
* �E�H�[���b�N�{�X�N���X��AI��
* �퓬��ԃN���X�̒�`.
*/
#pragma once

#include"IWarlockState.h"

class WarlockState_Combat : public IWarlockState
{
private:

	/** ���[�J���̏�ԃR�[�h. */
	enum class LocalStateCodeE
	{
		Invalid = -1,	//!< ����.
		Stand,			//!< ����.
		Chase,			//!< �Ǐ].
		Turn,			//!< ��].
		Attack,			//!< �U��.
		Damage,			//!< �_���[�W.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	WarlockState_Combat(Boss_Warlock* boss) :
		IWarlockState(boss)
	{
		InitLocalState();
	}

	/**
	* �f�X�g���N�^.
	*/
	~WarlockState_Combat()
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

	/**
	* ���[�J���̏�Ԃ�������.
	*/
	void InitLocalState();

private:

	Vector3 MoveDirection_ = Vector3::Zero;

};