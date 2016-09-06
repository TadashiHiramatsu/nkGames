#pragma once

class CPlayer : public CGameObject
{
public:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//立ち。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationJump,		//ジャンプ。
	};
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

	//アニメーション再生
	void PlayAnimation(AnimationNo animNo);

private:
	//回転
	void Rotation();
	//移動
	void Move();
private:
	CModelRender m_model; //モデル
	CLight m_light; //ライト
	CTexture m_normal; //法線テクスチャ
	CTexture m_spec; //スペキュラテクスチャ
	CAnimation* m_anim; //アニメーション
	AnimationNo currentAnimSetNo; //現在のアニメーション

	CTransform m_trans; //トランスフォーム
	
	D3DXVECTOR3 m_Target; //注視点
	D3DXVECTOR3 m_direction_Z;
	D3DXVECTOR3 m_direction_X;
	float m_TargetLen;
};