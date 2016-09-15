#pragma once

class CHead : public CGameObject
{
public:
	//コンストラクタ
	CHead();

	//デストラクタ
	~CHead();

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//描画
	void Render()override;

	//開放
	void Release()override;

	//コアのライト設定
	void SetLight(CLight* light)
	{
		m_model.SetLight(light);
	}

	//コアのカメラ設定
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