#pragma once

#include"IItem.h"

//�����A�C�e��
class EquipmentItem : public IItem
{
public:

	enum EquipmentType
	{
		BUKI, //����
		BOUGU, //�h��
	};

public:

	//�R���X�g���N�^
	EquipmentItem();

	//�f�X�g���N�^
	~EquipmentItem();

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