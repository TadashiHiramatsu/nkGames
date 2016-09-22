#pragma once

#include"CParts.h"

#include"CHead.h"
#include"CCore.h"
#include"CLeftArm.h"
#include"CRightArm.h"
#include"CLeg.h"

class CArmoredCore :public CGameObject
{
public:

	//コンストラクタ
	CArmoredCore();

	//デストラクタ
	~CArmoredCore();

	//初期化
	virtual void Init()override;

	//更新
	virtual void Update()override;

	//描画
	virtual void Render()override;

	//開放
	virtual void Release()override;

	//トランスフォームの設定
	void SetTranceform(CTransform* trans)
	{
		m_Tranceform = trans;
	}

	//ライトの設定
	void SetLight(CLight* light)
	{
		m_Light = light;
	}

	//カメラの設定
	void SetCamera(CCamera* camera)
	{
		m_Camera = camera;
	}

private:
	CTransform* m_Tranceform;
	CLight* m_Light;
	CCamera* m_Camera;

	//モデルたちテスト用
	CHead m_Head;
	CCore m_Core;
	CLeftArm m_LeftArm;
	CRightArm m_RightArm;
	CLeg m_Leg;
};