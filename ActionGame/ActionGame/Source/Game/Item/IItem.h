#pragma once

//�A�C�e���̊��N���X
//�A�C�e�������\�[�X�N���X�ň�������
//ID�Ŏ��ʂ���
class IItem
{
public:

	//���A���e�B�B�������ꂾ��
	enum RarityCode
	{
		Common, //�R�����B�ǂ��ł���ɓ���B
		Magic, //�}�W�b�N
		Rare, //���A�B
		Unique, //���j�[�N
	};

public:

private:
	int ID; //�A�C�e�������ʂ��邽�߂̃R�[�h
	char* Name; //�A�C�e���̖��́B�Q�[�����ŕ\���������
	RarityCode Rarity; //���A���e�B�B
};