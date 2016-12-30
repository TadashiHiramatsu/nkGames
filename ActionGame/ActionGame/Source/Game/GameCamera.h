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
		dirForward.y = 0.0f;		//Y������Ȃ��B
		dirForward.z = mViewInv->m[2][2];
		D3DXVec3Normalize(&dirForward, &dirForward);//Y����ł������Ă���̂Ő��K������B
		return dirForward;
	}

	D3DXVECTOR3& GetDirectionRight()
	{
		D3DXVECTOR3 dirRight;
		dirRight.x = mViewInv->m[0][0];
		dirRight.y = 0.0f;		//Y���͂���Ȃ��B
		dirRight.z = mViewInv->m[0][2];
		D3DXVec3Normalize(&dirRight, &dirRight);//Y����ł������Ă���̂Ő��K������B
		return dirRight;
	}

private:

	CCamera Camera;
	Player* player;

	const D3DXMATRIX* mViewInv;

	float distance; //����
};

extern GameCamera* g_MainCamera;