#pragma once

class CSkybox : public CGameObject
{
public:
	//コンストラクタ
	CSkybox();

	//デストラクタ
	~CSkybox();

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//描画
	void Render()override;

	//開放
	void Release()override;

	void SetPosition(D3DXVECTOR3& pos)
	{
		m_trans.SetPosition(pos);
	}

private:
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;
};