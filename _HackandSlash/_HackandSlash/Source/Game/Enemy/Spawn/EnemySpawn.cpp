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
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Start()
{

}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void EnemySpawn::Update()
{
	if (EnemyList_.size() <= Parameter_.EnemyMax_)
	{
		//�����X�^�[�̏o�������ő�ɑ������Ă��Ȃ��̂�
		if (Parameter_.SpawnTime_ <= SpawnLT_)
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
	D3DXVECTOR3 pos = D3DXVECTOR3((Random::value() - 0.5f) * Parameter_.Distance_, 0, (Random::value() - 0.5f) * Parameter_.Distance_);
	pos += Parameter_.Position_;
	
	//�o���ʒu��ݒ�
	enemy->SetPosition(pos);
	//�����X�^�[�Ƀv���C���[�̃|�C���^��ݒ�
	enemy->SetPlayer(Player_);
	//�����X�^�[�̏�����
	enemy->Start();

	//���X�g�Ƀ����X�^�[��o�^
	EnemyList_.push_back(enemy);

	//�o�����Ԃ̃��[�J���^�C����������
	SpawnLT_ = 0;

}