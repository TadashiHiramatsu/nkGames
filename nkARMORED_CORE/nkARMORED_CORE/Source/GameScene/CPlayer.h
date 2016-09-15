#pragma once

#include"..\Armoredcore\CLeg.h" //足

class CPlayer : public CGameObject
{
public:
	//コンストラクタ
	CPlayer();
	
	//デストラクタ
	~CPlayer();

	//初期化
	void Init()override;

	//更新
	void Update()override;
	
	//描画
	void Render()override;
	
	//開放
	void Release()override;

	CTransform* GetTrans()
	{
		return &m_trans;
	}

	void SetMesh(LPD3DXMESH mesh)
	{
		jimen = mesh;
	}

	void SetMatrixInv(D3DXMATRIX*  mi)
	{
		jimenwInv = mi;
	}

private:
	//回転
	void Rotation();
	//移動
	void Move();
	//地面との当たり判定
	void Collision();
private:
	CLight m_light; //ライト

	CTransform m_trans; //トランスフォーム
	
	D3DXVECTOR3 m_Target; //注視点
	D3DXVECTOR3 m_direction_Z;
	D3DXVECTOR3 m_direction_X;
	float m_TargetLen;

	LPD3DXMESH jimen;
	D3DXMATRIX* jimenwInv;

	//体構成練習中
	CLeg m_Leg;
};