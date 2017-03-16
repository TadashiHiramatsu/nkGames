/**
 * @file Source\Game\Monster\EnemySpawn.h
 *
 * �G�𐶂ݏo���@�\�N���X�̒�`.
 */
#pragma once

#include"../IEnemy.h"

 /**
 * �G�l�~�[�X�|�i�[�N���X�̓ǂݍ��݃f�[�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct EnemySpawnInfoS
{
public:

	/** ���S�n. */
	Vector3 Position_ = Vector3::Up;
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
	 * �I�[�o�[���C�h���Ă��Ȃ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Start(EnemySpawnInfoS info);

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

	/**
	* �X�V���s�����ǂ����̍X�V.
	*/
	float ToPlayerUpdate()
	{
		Vector3 ToPlayer;
		ToPlayer.Sub(Player_->Transform_.Position_, Transform_.Position_);
		ToPlayerLength_ = ToPlayer.Length();
		return ToPlayerLength_;
	}

private:

	/** ����. */
	float Distance_ = 0;
	/** �o���ő吔. */
	int EnemyMax_ = 10;
	/** ���x��. */
	int EnemyLevel_ = 1;
	/** �G�̎��. */
	int EnemyID_ = 0;

	/** �o�����������X�^�[��o�^����. */
	vector<IEnemy*> EnemyList_;
	
	/** �o���Ԋu. */
	float SpawnTime_ = 1;
	/** �o�����Ԃ̃��[�J���^�C��. */
	float SpawnLT_ = 0.0f;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

	/** �v���C���[�Ƃ̋���. */
	float ToPlayerLength_ = 0;

};