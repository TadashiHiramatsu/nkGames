/**
 * @file Source\Game\Monster\MonsterHabitat.cpp
 *
 * �����X�^�[�̏Z���N���X�̎���.
 */
#include"stdafx.h"
#include"MonsterHabitat.h"

#include"Monster_01.h"

/**
 * �R���X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
MonsterHabitat::MonsterHabitat()
{
}

/**
 * �f�X�g���N�^.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
MonsterHabitat::~MonsterHabitat()
{
}

/**
 * ������.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void MonsterHabitat::Start()
{
	for (int i = 0; i < Parameter_.InitMonsterNum_; i++)
	{
		Appearance();
	}
}

/**
 * �X�V.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
void MonsterHabitat::Update()
{
	if (MonsterList_.size() <= Parameter_.MonsterMax_)
	{
		//�����X�^�[�̏o�������ő�ɑ������Ă��Ȃ��̂�
		if (Parameter_.AppearanceTime_ <= AppearanceLT_)
		{
			//�o�����Ԃ��o�߂��Ă���̂ŏo��
			Appearance();
		}
		
		//�o�����Ԃ̃��[�J���^�C�������Z
		AppearanceLT_ += Time().DeltaTime();
	
	}

	//�����X�^�[���X�g�̃C�e���[�^���擾
	auto it = MonsterList_.begin();

	while (it != MonsterList_.end())
	{

		if (!(*it)->GetActive())
		{
			//�����X�^�[���폜
			delete (*it);

			//�����X�^�[�����X�g����폜
			it = MonsterList_.erase(it);

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
void MonsterHabitat::Render()
{
	for (auto it : MonsterList_)
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
void MonsterHabitat::Appearance()
{
	//�����X�^�[���쐬
	Monster_01* m = new Monster_01;

	//�o���ʒu���v�Z
	D3DXVECTOR3 pos = D3DXVECTOR3(Random().GetRandDouble0() * Parameter_.Distance_, 0, Random().GetRandDouble0() * Parameter_.Distance_);
	pos += Parameter_.Position_;
	//�o���ʒu��ݒ�
	m->SetPosition(pos);
	//�����X�^�[�Ƀv���C���[�̃|�C���^��ݒ�
	m->SetPlayer(Player_);
	//�����X�^�[�̏�����
	m->Start();

	//���X�g�Ƀ����X�^�[��o�^
	MonsterList_.push_back(m);

	//�o�����Ԃ̃��[�J���^�C����������
	AppearanceLT_ = 0;

}