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
	GameCamera()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~GameCamera()
	{
	}

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
	const Camera* GetCamera() const
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
	void SetPlayer(const Player* pla)
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
	const Vector3& GetDirectionForward() const
	{
		Vector3 dirForward;
		dirForward.x = ViewInvMatrix_->m[2][0];
		dirForward.y = 0.0f;		//Y軸いらない。
		dirForward.z = ViewInvMatrix_->m[2][2];

		//Y軸を打ち消しているので正規化する。
		dirForward.Normalize();
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
	const Vector3& GetDirectionRight() const
	{
		Vector3 dirRight;
		dirRight.x = ViewInvMatrix_->m[0][0];
		dirRight.y = 0.0f;		//Y軸はいらない。
		dirRight.z = ViewInvMatrix_->m[0][2];

		//Y軸を打ち消しているので正規化する。
		dirRight.Normalize();
		return dirRight;
	}

private:

	/** カメラ. */
	Camera Camera_;
	/** プレイヤー. */
	const Player* Player_ = nullptr;
	/** 距離. */
	float Distance_;
	/** 最大距離. */
	float DistanceMax_;

	/** ビュー行列の逆行列. */
	const Matrix* ViewInvMatrix_ = nullptr;

	/** 回転スピード.一秒間に回転する角度. */
	float SpinSpeed = 45.0f;

	/** プレイヤーの少し上を見る調整. */
	Vector3 PlusPosition_;

	/** カメラコリジョンクラス. */
	CameraCollision CameraCollision_;

};

/** グローバル. */
extern GameCamera* g_MainCamera;