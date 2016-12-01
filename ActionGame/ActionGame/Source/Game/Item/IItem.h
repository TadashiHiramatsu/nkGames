#pragma once

class IItem
{
public:

	//�A�C�e���̎��
	enum ItemType
	{
		Non, //�ݒ�Ȃ�
		UseItem, //����A�C�e��
	};

	//�A�C�e���p�����[�^
	struct ItemParameter
	{
		ItemParameter()
		{
			ID = 0;
			Name = "�������̃A�C�e��";
			IconFilePath = "Icon/NonData.png";
		}
		int ID;
		char* Name;
		char* IconFilePath;
	};

public:

	//�R���X�g���N�^
	IItem();

	//�f�X�g���N�^
	virtual ~IItem();

	//�f�[�^�̃��[�h
	virtual void Load();

	//������
	virtual void Init();

	//�X�V
	virtual void Update(){}

	//�`��
	virtual void Render();

	//���
	virtual void Release();

	//�N���b�N���ꂽ���̏���
	virtual void Click() = 0;

	ItemParameter GetParameter()
	{
		return IP;
	}

	void SetSTramsform(UITransform* _tf)
	{
		Image.SetTransform(_tf);
	}
		
protected:
	Image Image;

	ItemParameter IP;
};