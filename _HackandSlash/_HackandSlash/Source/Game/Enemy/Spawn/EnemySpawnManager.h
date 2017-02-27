/**
* �G�l�~�[�X�|�i�[�Ǘ��N���X�̒�`.
*/
#pragma once

#include"EnemySpawn.h"

/**
* �G�l�~�[�X�|�i�[�Ǘ��N���X.
*/
class EnemySpawnManager : public IGameObject
{
private:

	/** �G�l�~�[�X�|�i�[�ǂݍ��݃R�[�h. */
	enum ESReadCodeE
	{
		PositionX,	//!< ���WX.
		PositionY,	//!< ���WY.
		PositionZ,	//!< ���WZ.
		Distance,	//!< �o���͈�.
		EnemyMax,	//!< �G�o����.
		SpawnTime,	//!< �o������.
		EnemyLevel,	//!< �G���x��.
		EnemyID,	//!< �G�l�~�[ID.
	};

public:

	/**
	* �R���X�g���N�^.
	*/
	EnemySpawnManager()
	{
	}
	
	/**
	* �f�X�g���N�^.
	*/
	~EnemySpawnManager()
	{
	}

	/**
	* ������.
	*/
	void Start()override;
	
	/**
	* �v���C���[�̃|�C���^��ݒ�.
	*
	* @param [in]	p	�v���C���[�̃|�C���^.
 	*/
	void SetPlayer(Player* p)
	{
		Player_ = p;
	}

private:

	/** �G�l�~�[�X�|�[�����X�g. */
	list<EnemySpawn*> EnemySpawnList_;

	/** �v���C���[�̃|�C���^. */
	Player* Player_;

};