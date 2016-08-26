#pragma once

class CGameCamera : public CGameObject
{
public:
	//�R���X�g���N�^
	CGameCamera();

	//�f�X�g���N�^
	~CGameCamera();

	//������
	void Init()override;

	//�X�V
	void Update()override;

	//�`��
	void Render()override;

	//�J��
	void Release()override;

	//�J�������擾
	CCamera* GetCamera()
	{
		return &m_camera;
	}


private:
	CCamera m_camera;
};

extern CGameCamera g_camera;