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
	void BeforeUpdate();

	//�`��
	void Render()override{}

	//�J��
	void Release()override;

	//�J�������擾
	CCamera* GetCamera()
	{
		return &m_camera;
	}

	void SetPlayerTarget(const D3DXVECTOR3& target)
	{
		m_PlayerTarget = target;
	}

	void SetPlayerPosition(const D3DXVECTOR3& pos)
	{
		m_PlayerPosition = pos;
	}

	D3DXVECTOR3 GetDirection()
	{
		return m_Direction;
	}

private:
	CCamera m_camera;
	D3DXVECTOR3 m_PlayerTarget;
	D3DXVECTOR3 m_PlayerPosition;
	D3DXVECTOR3 m_DefaultPosition;

	D3DXVECTOR3 m_Direction;
};

extern CGameCamera g_camera;