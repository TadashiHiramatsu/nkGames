#pragma once

class IWindow
{
public:

	//�R���X�g���N�^
	IWindow();

	//�f�X�g���N�^
	virtual ~IWindow();

	//������
	virtual void Init();

	//�X�V
	virtual void Update();

	//�`��
	virtual void Render();

	//���
	virtual void Release();

protected:


};