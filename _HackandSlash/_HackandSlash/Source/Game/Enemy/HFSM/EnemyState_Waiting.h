/**
* �G�̑ҋ@��ԃN���X�̒�`.
*/
#pragma once

#include"IEnemyState.h"

/**
* �G�̑ҋ@��ԃN���X.
*/
class EnemyState_Waiting : public IEnemyState
{
private:

	/** ���[�J���̏�ԃR�[�h. */
	enum class LocalStateCodeE
	{
		Stand,	//!< �������.
	};

public:

	/**
	* �R���X�g���N�^.
	*
	* @param enemy	�����̃|�C���^.
	*/
	EnemyState_Waiting(IEnemy* enemy);
	

	/**
	* �f�X�g���N�^.
	*/
	~EnemyState_Waiting()
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

	/** �ړI�n. */
	Vector3 Destination_ = Vector3::Zero;

};