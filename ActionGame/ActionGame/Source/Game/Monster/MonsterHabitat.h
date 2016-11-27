#pragma once

#include"IMonster.h"

//�����X�^�[�̏Z��
//���S�n���烂���X�^�[�͏o������
class MonsterHabitat
{
public:
	struct MHParameter
	{
		D3DXVECTOR3 Position; //���S�n
		float Distance; //����
		int MonsterID; //�����X�^�[�̎��
		int MonsterMax; //�o���ő吔
		float Time; //�o���Ԋu
	}; 
public:
	MonsterHabitat();
	~MonsterHabitat();
	void Init(MHParameter& _mhp);
	void Init();
	void Update();
	void Render();
	void Release();

private:
	MHParameter MHP; //�����X�^�[�n���^�[�|�[�^�u������Ȃ���
	vector<IMonster*> MonsterList;
	int NowMonsterNum = 0; //���݂̃����X�^�[��
	float LocalTime = 0; 
};