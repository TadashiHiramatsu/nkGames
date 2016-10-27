#pragma once

#include"../Physics/CMeshCollider.h"
#include"../Physics/CRigidBody.h"

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

	//剛体初期化
	void InitRigidBody();

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

	bool m_isBreak;
	D3DXMATRIX* m_mWorld; //ワールド行列
	CMeshCollider m_MeshCollider; //メッシュコライダー
	CRigidBody m_RigidBody; //剛体
};
