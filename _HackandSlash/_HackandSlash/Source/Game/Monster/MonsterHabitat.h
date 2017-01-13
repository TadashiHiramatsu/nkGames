/**
 * @file Source\Game\Monster\MonsterHabitat.h
 *
 * �����X�^�[�̏Z���N���X�̒�`.
 */
#pragma once

#include"IMonster.h"

/**
 * �����X�^�[�̏Z��.
 * ���S�n���烂���X�^�[�͏o������.
 * ����o���|�C���g�ɕω�����\������
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class MonsterHabitat : public IGameObject
{
public:

	/**
	 * MonsterHabitat�N���X�̃p�����[�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct MHParameterS
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/11
		 */
		MHParameterS()
		{
			Position_ = D3DXVECTOR3(0, 1, 0);
			Distance_ = 10;
			MonsterID_ = 1;
			MonsterMax_ = 10;
			AppearanceTime_ = 5;
			InitMonsterNum_ = 5;
		}

	public:

		/** ���S�n. */
		D3DXVECTOR3 Position_;
		/** ����. */
		float Distance_;
		/** �����X�^�[�̎��. */
		int MonsterID_;
		/** �o���ő吔. */
		int MonsterMax_;
		/** �o���Ԋu. */
		float AppearanceTime_;
		/** ���������̃����X�^�[�̐�. */
		int InitMonsterNum_;
	
	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	MonsterHabitat();

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~MonsterHabitat();

public:

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start()override;

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Update()override;

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Render()override;

	/**
	 * �����X�^�[�o���֐�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Appearance();

	/**
	 * �v���C���[�̃|�C���^��ݒ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 *
	 * @param [in,out] p If non-null, the Player to process.
	 */
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** �����X�^�[�n���^�[�|�[�^�u������Ȃ���. */
	MHParameterS Parameter_;
	/** �o�����������X�^�[��o�^����. */
	vector<IMonster*> MonsterList_;
	/** �o�����Ԃ̃��[�J���^�C��. */
	float AppearanceLT_ = 0.0f;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

};