/**
 * @file Source\Game\Monster\EnemySpawn.h
 *
 * �G�𐶂ݏo���@�\�N���X�̒�`.
 */
#pragma once

#include"../IEnemy.h"

/**
 * �G�l�~�[�X�|�i�[�N���X.
 * ���S�n����G�͏o������.
 * ����o���|�C���g�ɕω�����\������
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
class EnemySpawn : public IGameObject
{
public:

	/**
	 * �G�l�~�[�X�|�i�[�N���X�̃p�����[�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	struct ESParameterS
	{
	public:

		/** ���S�n. */
		D3DXVECTOR3 Position_ = D3DXVECTOR3(0, 0, 0);
		/** ����. */
		float Distance_ = 0;
		/** �o���ő吔. */
		int EnemyMax_ = 10;
		/** �o���Ԋu. */
		float SpawnTime_ = 1;
		/** ���x��. */
		int EnemyLevel_ = 1;
		/** �G�̎��. */
		int EnemyID_ = 0;

	};

public:

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	EnemySpawn()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	~EnemySpawn()
	{
	}

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
	ESParameterS Parameter_;

	/** �o�����������X�^�[��o�^����. */
	vector<IEnemy*> EnemyList_;
	
	/** �o�����Ԃ̃��[�J���^�C��. */
	float SpawnLT_ = 0.0f;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

};