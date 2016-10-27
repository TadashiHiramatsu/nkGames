#pragma once

class GameCamera : public CGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Init()override;
	void Update()override;
	void Render()override{}
	void Release()override;

	CCamera* GetCamera()
	{
		return &Camera;
	}

	void SetPlayerTranceform(CTransform* trans)
	{
		m_PlayerTranceform = trans;
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
	CTransform* m_PlayerTranceform;

	const D3DXMATRIX* mViewInv;
};

extern GameCamera MainCamera;