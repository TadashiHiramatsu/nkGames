/**
 * @file	Source\Game\GameCamera.h
 *
 * ゲームカメラクラスの定義.
 */
#pragma once

#include"Player\Player.h"

/**
 * ゲームカメラクラス.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class GameCamera : public IGameObject
{
public:

	/**
	 * コンストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	GameCamera();

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~GameCamera();

	/**
	 * 初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * 更新.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * カメラを取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	Null if it fails, else the camera.
	 */
	Camera* GetCamera()
	{
		return &Camera_;
	}

	/**
	 * Sets player pointer.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	pla	If non-null, the pla.
	 */
	void SetPlayer(Player* pla)
	{
		Player_ = pla;
	}

	/**
	 * カメラの前方向を取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction forward.
	 */
	D3DXVECTOR3& GetDirectionForward()
	{
		D3DXVECTOR3 dirForward;
		dirForward.x = ViewInvMatrix_->m[2][0];
		dirForward.y = 0.0f;		//Y軸いらない。
		dirForward.z = ViewInvMatrix_->m[2][2];
		D3DXVec3Normalize(&dirForward, &dirForward);//Y軸を打ち消しているので正規化する。
		return dirForward;
	}

	/**
	 * カメラの右方向を取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction right.
	 */
	D3DXVECTOR3& GetDirectionRight()
	{
		D3DXVECTOR3 dirRight;
		dirRight.x = ViewInvMatrix_->m[0][0];
		dirRight.y = 0.0f;		//Y軸はいらない。
		dirRight.z = ViewInvMatrix_->m[0][2];
		D3DXVec3Normalize(&dirRight, &dirRight);//Y軸を打ち消しているので正規化する。
		return dirRight;
	}

private:

	/** カメラ. */
	Camera Camera_;
	/** プレイヤー. */
	Player* Player_;
	/** 距離. */
	float Distance_;
	/** The view inverse matrix. */
	const D3DXMATRIX* ViewInvMatrix_;
};

/** グローバル. */
extern GameCamera* g_MainCamera;