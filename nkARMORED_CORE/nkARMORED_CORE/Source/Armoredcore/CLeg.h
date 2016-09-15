#pragma once

class CLeg : public CGameObject
{
public:
	//コンストラクタ
	CLeg();

	//デストラクタ
	~CLeg();

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//描画
	void Render()override;

	//開放
	void Release()override;

	void SetLight(CLight* light)
	{
		m_model.SetLight(light);
	}

	void SetCamera(CCamera* camera)
	{
		m_model.SetCamera(camera);
	}

	void SetParentMatrix(D3DXMATRIX* parent)
	{
		m_model.SetParentMatrix(parent);
	}

private:
	CACModelRender m_model; //左腕のモデル
	CTransform m_trans; //トランスフォーム
};