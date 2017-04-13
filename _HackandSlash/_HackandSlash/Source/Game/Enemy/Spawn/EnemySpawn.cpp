/**
 * @file Source\Game\Monster\EnemySpawn.cpp
 *
 * �G�𐶂ݏo���@�\�N���X�̎���.
 */
#include"stdafx.h"
#include"EnemySpawn.h"

#include"../Enemy_01.h"

/**
 * ������.
 * �I�[�o�[���C�h���Ă��Ȃ�.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Start(EnemySpawnInfoS info)
{
	//�ʒu��ݒ�
	Transform_.Position_ = info.Position_;

	//�o���͈�
	Distance_ = info.Distance_;

	//�G�l�~�[��
	EnemyMax_ = info.EnemyMax_;

	//�G�l�~�[���x��
	EnemyLevel_ = info.EnemyLevel_;

	//ID�ݒ�
	EnemyID_ = info.EnemyID_;

	//�o�����x
	SpawnTime_ = info.SpawnTime_;

	//��ԏ��߂ɏo������.
	SpawnLT_ = 999;
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Update()
{
	if (EnemyList_.size() < EnemyMax_)
	{
		//�����X�^�[�̏o�������ő�ɑ������Ă��Ȃ��̂�
		if (SpawnTime_ <= SpawnLT_)
		{
			//�o�����Ԃ��o�߂��Ă���̂ŏo��
			Appearance();
		}
		
		//�o�����Ԃ̃��[�J���^�C�������Z
		SpawnLT_ += Time().DeltaTime();
	
	}

	//�����X�^�[���X�g�̃C�e���[�^���擾
	auto& it = EnemyList_.begin();

	while (it != EnemyList_.end())
	{

		if (!(*it)->GetActive())
		{
			//�����X�^�[���폜
			delete (*it);

			//�����X�^�[�����X�g����폜
			it = EnemyList_.erase(it);
			
			continue;
		}

		//�X�V
		(*it)->Update();
	
		it++;
	}

}

/**
 * �`��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Render()
{
	for (auto& it : EnemyList_)
	{
		it->Render();
	}
}

/**
 * �����X�^�[�o���֐�.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Appearance()
{
	//�����X�^�[���쐬
	Enemy_01* enemy = new Enemy_01();

	//�o���ʒu���v�Z
	Vector3 pos = Vector3((Random().value() - 0.5f) * Distance_, 0, (Random().value() - 0.5f) * Distance_);
	pos.Add(Transform_.Position_);
	
	//�o���ʒu��ݒ�
	enemy->SetPosition(pos);
	//�����X�^�[�Ƀv���C���[�̃|�C���^��ݒ�
	enemy->SetPlayer(Player_);
	//���x����ݒ�
	enemy->SetLevel(EnemyLevel_);
	//�����X�^�[�̏�����
	enemy->Start();

	//���X�g�Ƀ����X�^�[��o�^
	EnemyList_.push_back(enemy);

	//�o�����Ԃ̃��[�J���^�C����������
	SpawnLT_ = 0;

}