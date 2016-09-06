#pragma once

class CGameCamera : public CGameObject
{
public:
	//コンストラクタ
	CGameCamera();

	//デストラクタ
	~CGameCamera();

	//初期化
	void Init()override;

	//更新
	void Update()override;
	void BeforeUpdate();

	//描画
	void Render()override{}

	//開放
	void Release()override;

	//カメラを取得
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