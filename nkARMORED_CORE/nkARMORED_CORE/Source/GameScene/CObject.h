#pragma once

class CObject : public CGameObject
{
public:
	//コンストラクタ
	CObject();

	//デストラクタ
	~CObject();

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//描画
	void Render()override;

	//開放
	void Release()override;
private:
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;
};