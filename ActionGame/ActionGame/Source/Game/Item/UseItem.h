#pragma once

#include"IItem.h"

//�g�p�A�C�e��
class UseItem : public IItem
{
public:

	//�R���X�g���N�^
	UseItem();

	//�f�X�g���N�^
	~UseItem();

	//�f�[�^�̃��[�h
	void Load()override;

	//������
	void Init()override;

	//�X�V
	 void Update()override;

	//�`��
	 void Render()override;

	//���
	 void Release()override;

	//�N���b�N���ꂽ���̏���
	 void Click()override;

private:

};