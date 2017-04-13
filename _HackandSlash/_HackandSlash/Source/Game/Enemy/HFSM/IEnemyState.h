/**
* �GAI�Ŏg�p����HFSM�̊��N���X�̒�`.
*/
#pragma once

#include"../IEnemy.h"

/**
* �G�̏�Ԃ̊��N���X.
*/
class IEnemyState : Noncopyable
{
public:

	/**
	* �R���X�g���N�^.
	*
	* @param enemy	���g�̃|�C���^.
	*/
	IEnemyState(IEnemy* enemy)
	{
		Enemy_ = enemy;
	}

	/**
	* �f�X�g���N�^.
	*/
	virtual ~IEnemyState()
	{
	}
	
	/**
	* �J�n����.
	* ���̏�ԂɑJ�ڂ������Ɏ��s�����.
	*/
	virtual void Entry()
	{
		LocalState_ = -1;
	}

	/**
	* �X�V����.
	* ���̏�Ԃ̎��ɖ��t���[�����s�����.
	*/
	virtual void Update()
	{
	}

	/**
	* �I������.
	* ���̏�Ԃ���J�ڂ������Ɏ��s�����.
	*/
	virtual void Exit()
	{
	}

protected:

	/**
	* ���[�J���̏�Ԃ�J�ڂ���.
	*
	* @param nextstate	�J�ڌ�̏��.
	*/
	void ChangeLocalState(int nextstate)
	{
#ifdef _DEBUG
		if (nextstate < 0 && LocalStateList_.size() <= nextstate)
		{
			NK_ASSERT(false, "���[�J���̏�Ԃɓo�^����Ă��܂���");
			return;
		}
#endif // _DEBUG

		if (LocalState_ != -1)
		{
			//���[�J���̏�Ԃ��ݒ肳��Ă�����I���������s��.
			LocalStateList_[LocalState_]->Exit();
		}
		
		//���̏�ԂɑJ��.
		LocalState_ = nextstate;
		//�J�n�������s��.
		LocalStateList_[LocalState_]->Entry();
	}

protected:

	/** ���[�J���̏�ԃ��X�g. */
	vector<IEnemyState*> LocalStateList_;
	/** ���[�J���̏��. */
	int LocalState_ = -1;

	/** �G�l�~�[�N���X�̃|�C���^. */
	IEnemy* Enemy_ = nullptr;

};