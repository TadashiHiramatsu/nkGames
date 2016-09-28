#pragma once

enum EDir
{
	Right = -1,
	Left = 1
};

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

	void SetPlayerTarget(D3DXVECTOR3* target)
	{
		m_PlayerTarget = target;
	}

	void SetPlayerTranceform(CTransform* trans)
	{
		m_PlayerTranceform = trans;
	}

	D3DXVECTOR3 GetDirection()
	{
		return m_Direction;
	}

	void ReversalDirection(EDir dir)
	{
		m_Dir = dir;
	}

private:
	CCamera m_camera;
	D3DXVECTOR3* m_PlayerTarget;
	CTransform* m_PlayerTranceform;
	D3DXVECTOR3 m_DefaultPosition;

	D3DXVECTOR3 m_Direction;
	
	EDir m_Dir;
};

extern CGameCamera g_camera;