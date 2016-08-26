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

	//描画
	void Render()override;

	//開放
	void Release()override;

	//カメラを取得
	CCamera* GetCamera()
	{
		return &m_camera;
	}


private:
	CCamera m_camera;
};

extern CGameCamera g_camera;