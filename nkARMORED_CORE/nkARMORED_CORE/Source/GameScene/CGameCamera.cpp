#include"stdafx.h"
#include"CGameCamera.h"

CGameCamera g_camera;

CGameCamera::CGameCamera():
	m_DefaultPosition(D3DXVECTOR3(1.0f, 2.0f, 0.0f)),
	m_PlayerTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_PlayerPosition(D3DXVECTOR3(0.0f,0.0f,0.0f))
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
	D3DXVECTOR3 dir = m_PlayerPosition - m_PlayerTarget;
	D3DXVec3Normalize(&dir, &dir);
	dir *= 5;

	m_camera.SetPosition(dir + m_DefaultPosition + m_PlayerPosition);
	m_camera.Update();
}

void CGameCamera::BeforeUpdate()
{
	m_Direction = m_PlayerTarget - m_camera.GetPosition();
	m_Direction.y = 0.0f;
	D3DXVec3Normalize(&m_Direction, &m_Direction);
}

void CGameCamera::Release()
{

}