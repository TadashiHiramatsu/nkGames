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
	CModelRender m_model;
	CTransform m_trans;
	CLight m_light;
	CTexture normal; //法線
	CAnimation* m_anim;
	AnimationNo currentAnimSetNo;
};