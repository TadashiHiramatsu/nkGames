#include"Player.h"

void CPlayer::Initialize(CDungeon* pDun)
{
	XfileName = _T("XFile\\Player.x");
	LifePoint = 500.0f;
	Damage = 20.0f;
	Radius = 5.0f;
	Speed = 2.0f;
	cameras = 0.05;
	C3DCharacter::Initialize(pDun);
	m_camesa.Initialize();
}
void CPlayer::Updata()
{
	D3DXMatrixIdentity(&matWorld);

	this->setFront(vec3Trans, m_camesa.GetVector());
	vec3Front.x *= Speed;
	vec3Front.z *= Speed;
	
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixLookAtLH(&matRot, &D3DXVECTOR3(vec3Trans + vec3Front), &vec3Trans, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixInverse(&matRot, NULL, &matRot);
	matRot._41 = 0.0f;
	matRot._42 = 0.0f;
	matRot._43 = 0.0f;

	if (GetAsyncKeyState(VK_W) & 0x8000)
	{
		vec3Trans.x += vec3Front.x;
		vec3Trans.z += vec3Front.z;
		if (WallCollision(vec3Trans))
		{
			vec3Trans.x -= vec3Front.x;
			vec3Trans.z -= vec3Front.z;
		}

	}
	if (GetAsyncKeyState(VK_S) & 0x8000)
	{
		vec3Trans.x -= vec3Front.x;
		vec3Trans.z -= vec3Front.z;
		if (WallCollision(vec3Trans))
		{
			vec3Trans.x += vec3Front.x;
			vec3Trans.z += vec3Front.z;
		}
	}

	if (GetAsyncKeyState(VK_D) & 0x8000)
	{
		vec3Trans.x += vec3Front.z;
		vec3Trans.z -= vec3Front.x;
		if (WallCollision(vec3Trans))
		{
			vec3Trans.x -= vec3Front.z;
			vec3Trans.z += vec3Front.x;
		}
	}
	if (GetAsyncKeyState(VK_A) & 0x8000)
	{
		vec3Trans.x -= vec3Front.z;
		vec3Trans.z += vec3Front.x;
		if (WallCollision(vec3Trans))
		{
			vec3Trans.x += vec3Front.z;
			vec3Trans.z -= vec3Front.x;
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (Key == false)
		{
			flg = true;
			Key = true;
		}
	}
	

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		if (Key == false)
		{
			Key = true;
			cameras -= 0.01f;
			if (cameras <= 0.00f)
			{
				cameras = 0.05f;
			}
		}
	}
	else
	{
		Key = false;
	}


	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_camesa.RotLongitudinal(cameras);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_camesa.RotLongitudinal(-cameras);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_camesa.RotTransversal(-cameras);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_camesa.RotTransversal(cameras);
	}
	m_camesa.SerBase(vec3Trans);

	
}