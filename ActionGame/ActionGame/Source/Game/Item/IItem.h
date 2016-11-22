#pragma once

class IItem
{
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
	virtual void Update();

	//�`��
	virtual void Render();

	//���
	virtual void Release();

	int GetID()
	{
		return ID;
	}

	void SetSTramsform(SpriteTransform* _st)
	{
		Sprite.SetSTransform(_st);
	}

	//�N���b�N���ꂽ���̏���
	virtual void Click();
		
protected:
	CSprite Sprite;

	int ID;
	char* Name;
};