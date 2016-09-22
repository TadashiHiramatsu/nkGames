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
		D3DXFRAME_DERIVED* frame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ACModel.GetFrame(), pass);
		return &frame->CombinedTransformationMatrix;
	}

protected:
	CACModelRender m_ACModel; //モデル
	CTransform m_Transform; //トランスフォーム
	CAnimation m_Animation; //アニメーション管理
};
