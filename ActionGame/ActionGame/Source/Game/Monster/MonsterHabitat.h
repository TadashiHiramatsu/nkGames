#pragma once

#include"IMonster.h"

//�����X�^�[�̏Z��
//���S�n���烂���X�^�[�͏o������
class MonsterHabitat : public IGameObject
{
public:

	//MonsterHabitat�N���X�̃p�����[�^
	struct MHParameter
	{
		MHParameter()
		{
			Position = D3DXVECTOR3(0, 1, 0);
			Distance = 10;
			MonsterID = 1;
			MonsterMax = 10;
			Time = 5;
			InitMonsterNum = 5;
		}
		D3DXVECTOR3 Position; //���S�n
		float Distance; //����
		int MonsterID; //�����X�^�[�̎��
		int MonsterMax; //�o���ő吔
		float Time; //�o���Ԋu
		int InitMonsterNum; //���������̃����X�^�[�̐�
	};

public:

	//�R���X�g���N�^
	MonsterHabitat();
	//�f�X�g���N�^
	~MonsterHabitat();

public:

	//������
	void Start()override;
	//�X�V
	void Update()override;
	//�`��
	void Render()override;

	//�����X�^�[�o���֐�
	void Appearance();

private:
	MHParameter Parameter; //�����X�^�[�n���^�[�|�[�^�u������Ȃ���
	vector<IMonster*> MonsterList;
	int NowMonsterNum = 0; //���݂̃����X�^�[��
	float LocalTime = 0; 
};