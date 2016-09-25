#include"stdafx.h"
#include"CGameCamera.h"

CGameCamera g_camera;

CGameCamera::CGameCamera() :
	m_DefaultPosition(D3DXVECTOR3(0.0f, 7.0f, 0.0f)),
	m_PlayerTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_PlayerPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_Dir(EDir::Left)
{

}

CGameCamera::~CGameCamera()
{

}

void CGameCamera::Init()
{
	m_camera.SetPetson(EPerson::third);
	m_camera.SetPosition(m_DefaultPosition + m_PlayerPosition);
	m_camera.SetTarget(m_PlayerTarget);
	m_camera.Update();
}

void CGameCamera::Update()
{
	m_camera.SetTarget(m_PlayerTarget);

	D3DXVECTOR3 dirZ, dirX;
	dirZ = m_PlayerPosition - m_PlayerTarget;
	D3DXVec3Normalize(&dirZ, &dirZ);
	D3DXVec3Cross(&dirX, &dirZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	dirZ *= 20;
	dirX *= 8;

	static float dir = 1.0f;
	if (m_Dir == EDir::Left)
	{
		if (dir < 1.0f)
		{
			dir += 0.1f;
		}
	}
	if (m_Dir == EDir::Right)
	{
		if (dir > -1.0f)
		{
			dir -= 0.1f;
		}
	}

	D3DXVECTOR3 pos = dirZ + m_DefaultPosition + m_PlayerPosition + dirX * dir; //移動先のポジション

	D3DXVECTOR3 camerapos = m_camera.GetPosition(); //現在のポジション
	D3DXVECTOR3 toPos = pos - camerapos; //現在のポジションから移動先のポジションへのベクトル

	m_camera.SetPosition(toPos + camerapos);


	m_Direction = m_PlayerTarget - m_camera.GetPosition();
	m_Direction.y = 0.0f;
	D3DXVec3Normalize(&m_Direction, &m_Direction);

	m_camera.Update();
}

void CGameCamera::BeforeUpdate()
{
	
}

void CGameCamera::Release()
{

}