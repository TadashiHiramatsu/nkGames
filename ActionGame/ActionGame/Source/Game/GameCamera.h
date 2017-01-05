/**
 * @file	Source\Game\GameCamera.h
 *
 * Declares the game camera class.
 */
#pragma once

#include"Player\Player.h"

/**
 * A game camera.
 *
 * @author	HiramatsuTadashi
 * @date	2016/12/31
 */
class GameCamera : public IGameObject
{
public:

	/**
	 * Default constructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	GameCamera();

	/**
	 * Destructor.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	~GameCamera();

	/**
	 * Starts this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Start()override;

	/**
	 * Updates this object.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 */
	void Update()override;

	/**
	 * Gets the camera.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	Null if it fails, else the camera.
	 */
	CCamera* GetCamera()
	{
		return &Camera;
	}

	/**
	 * Sets player pointer.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @param [in,out]	_pla	If non-null, the pla.
	 */
	void SetPlayerPointer(Player* _pla)
	{
		player = _pla;
	}

	/**
	 * Gets direction forward.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction forward.
	 */
	D3DXVECTOR3& GetDirectionForward()
	{
		D3DXVECTOR3 dirForward;
		dirForward.x = mViewInv->m[2][0];
		dirForward.y = 0.0f;		//Y軸いらない。
		dirForward.z = mViewInv->m[2][2];
		D3DXVec3Normalize(&dirForward, &dirForward);//Y軸を打ち消しているので正規化する。
		return dirForward;
	}

	/**
	 * Gets direction right.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2016/12/31
	 *
	 * @return	The direction right.
	 */
	D3DXVECTOR3& GetDirectionRight()
	{
		D3DXVECTOR3 dirRight;
		dirRight.x = mViewInv->m[0][0];
		dirRight.y = 0.0f;		//Y軸はいらない。
		dirRight.z = mViewInv->m[0][2];
		D3DXVec3Normalize(&dirRight, &dirRight);//Y軸を打ち消しているので正規化する。
		return dirRight;
	}

private:

	/** The camera. */
	CCamera Camera;

	/** The player. */
	Player* player;

	/** The view inverse. */
	const D3DXMATRIX* mViewInv;

	/** 距離. */
	float distance;
};

/** The main camera. */
extern GameCamera* g_MainCamera;