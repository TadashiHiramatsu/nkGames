#pragma once

class CParts : public CGameObject
{
public:

	//コンストラクタ
	CParts();

	//デストラクタ
	~CParts();

	//初期化
	virtual void Init()override;

	//更新
	virtual void Update()override;

	//描画
	virtual void Render()override;

	//開放
	virtual void Release()override;

	//読み込み
	void LoadModel(const char* filepass);

	inline CACModelRender* GetACModel()
	{
		return &m_ACModel;
	}

	inline CAnimation* GetAnimation()
	{
		return &m_Animation;
	}

	inline D3DXMATRIX* GetMatrix(const char* pass)
	{
		return m_ACModel.FindBoneWorldMatrix(pass);
	}

protected:
	CACModelRender m_ACModel; //モデル
	CTransform m_Transform; //トランスフォーム
	CAnimation m_Animation; //アニメーション管理
};
