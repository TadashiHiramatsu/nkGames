#include"stdafx.h"
#include"CGameCamera.h"

CGameCamera g_camera;

CGameCamera::CGameCamera()
{

}

CGameCamera::~CGameCamera()
{

}

void CGameCamera::Init()
{
	m_camera.SetPosition(D3DXVECTOR3(0.0f, 0.5f, 1.0f));
	m_camera.SetTarget(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_camera.SetDistance(5);
	m_camera.Update();
}

void CGameCamera::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_camera.SpinHorizontally(-0.05f);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_camera.SpinHorizontally(0.05f);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_camera.SpinVertically(0.05f);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_camera.SpinVertically(-0.05f);
	}


	m_camera.Update();
}

void CGameCamera::Render()
{

}

void CGameCamera::Release()
{

}

