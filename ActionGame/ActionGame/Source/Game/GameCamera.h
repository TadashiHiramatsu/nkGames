#pragma once

#include"Player\Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Start()override;
	void Update()override;

	CCamera* GetCamera()
	{
		return &Camera;
	}

	void SetPlayerPointer(Player* _pla)
	{
		player = _pla;
	}

	D3DXVECTOR3& GetDirectionForward()
	{
		D3DXVECTOR3 dirForward;
		dirForward.x = mViewInv->m[2][0];
		dirForward.y = 0.0f;		//Y軸いらない。
		dirForward.z = mViewInv->m[2][2];
		D3DXVec3Normalize(&dirForward, &dirForward);//Y軸を打ち消しているので正規化する。
		return dirForward;
	}

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

	CCamera Camera;
	Player* player;

	const D3DXMATRIX* mViewInv;

	float distance; //距離
};

extern GameCamera* g_MainCamera;