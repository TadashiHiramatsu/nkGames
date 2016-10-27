#include"stdafx.h"
#include"CPlayer.h"
#include"CGameCamera.h"

CPlayer::CPlayer():
	m_TargetLen(30),
	jimen(nullptr),
	gravity( 9.8 * 0.0016)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_trans.SetPosition(D3DXVECTOR3(0.0f,100.0f,0.0f));

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 20.5f, 19.5f) + m_trans.GetPosition());
	Shadow().SetLightTarget(m_trans.GetPosition());

	m_Target = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Target *= m_TargetLen;
	m_Target.y = m_trans.GetPosition().y;
	m_ArmoredCore.SetTranceform(&m_trans);
	m_ArmoredCore.SetLight(&m_light);
	m_ArmoredCore.SetCamera(g_camera.GetCamera());
	m_ArmoredCore.Init();

	g_camera.SetPlayerTarget(&m_Target);
	g_camera.SetPlayerTranceform(&m_trans);
}

void CPlayer::Update()
{
	Rotation();
	Move();
	Collision();

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 20.5f, 19.5f)*3 + m_trans.GetPosition());
	Shadow().SetLightTarget(m_trans.GetPosition());

	m_ArmoredCore.Update();
}

void CPlayer::Render()
{
	m_ArmoredCore.Render();
}

void CPlayer::Release()
{
	m_ArmoredCore.Release();
}

void CPlayer::Rotation()
{
	//プレイヤーの視点から注視点のベクトルを作成
	D3DXVECTOR3 m_toTarget = m_Target - m_trans.GetPosition();
	
	static float rots = 0.1f;
	//回転させてる
	D3DXMATRIX tmp,tmp2;
	D3DXMatrixIdentity(&tmp);
	D3DXMatrixIdentity(&tmp2);

	D3DXVECTOR3 dirZ,dirX;
	D3DXVec3Normalize(&dirZ, &m_toTarget);
	D3DXVec3Cross(&dirX, &dirZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//下
	if (XInput().GetStickR_Y() <= -1)
	{
		D3DXMatrixRotationAxis(&tmp, &dirX, -rots);
	}
	if (XInput().GetStickR_Y() >= 1)
	{
		D3DXMatrixRotationAxis(&tmp, &dirX, rots);
	}

	static int time[2] = { 0 };
	if (XInput().GetStickR_X() <= -1)
	{
		time[0]++;
		D3DXMatrixRotationY(&tmp2, -rots);
	}
	else
	{
		time[0] = 0;
	}
	if (XInput().GetStickR_X() >= 1)
	{
		time[1]++;
		D3DXMatrixRotationY(&tmp2, rots);
	}
	else
	{
		time[1] = 0;
	}

	static int timer = 6;
	if (time[0] >= timer && time[1] == 0)
	{
		g_camera.ReversalDirection(EDir::Right);
	}
	if (time[1] >= timer && time[0] == 0)
	{
		g_camera.ReversalDirection(EDir::Left);
	}

	//回転
	tmp *= tmp2;
	D3DXVec3TransformCoord(&m_toTarget, &m_toTarget, &tmp);

	//回転した注視点
	D3DXVec3Normalize(&m_toTarget, &m_toTarget);

	m_toTarget.y = min(0.7f, m_toTarget.y);
	m_toTarget.y = max(-0.7f, m_toTarget.y);

	m_Target = m_toTarget * m_TargetLen + m_trans.GetPosition();

	//進行方向と横方向を作成
	m_direction_Z = g_camera.GetDirection();
	D3DXVec3Normalize(&m_direction_Z, &m_direction_Z);
	D3DXVec3Cross(&m_direction_X, &m_direction_Z, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	{
		float angle = acos(D3DXVec3Dot(&m_direction_X, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &m_direction_X, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		D3DXQUATERNION mRotation = m_trans.GetRotation();
		D3DXQuaternionRotationAxis(&mRotation, &axis, -angle);
		m_trans.SetRotation(mRotation);
	}
}

void CPlayer::Move()
{
	move.x = 0;
	move.z = 0;
	static float Speed = 1.0f;
	if(XInput().GetStickL_X() <= -1)
	{ 
		move += m_direction_X* Speed;
	}
	if (XInput().GetStickL_X() >= 1)
	{
		move -= m_direction_X * Speed;
	}
	if (XInput().GetStickL_Y() <= -1)
	{
		move -= m_direction_Z* Speed;
	}
	if (XInput().GetStickL_Y() >= 1)
	{
		move += m_direction_Z* Speed;
	}


	if (XInput().IsTrigger(EButton::enButtonLB1))
	{
		move.y += 2;
	}

	move.y -= gravity;
	//boost -= gravity;//重力
	//move.y = boost; 
	m_trans.AddPosition(move);
	m_Target += move;

	/*move = D3DXVECTOR3(0, 0, 0);

	if (XInput().GetStickL_X() <= -1 && XInput().IsTrigger(EButton::enButtonLB1))
	{
		move += m_direction_X *= 3.0f;
	}
	if (XInput().GetStickL_X() >= 1 && XInput().IsTrigger(EButton::enButtonLB1))
	{
		move -= m_direction_X *= 3.0f;
	}
	m_trans.AddPosition(move);
	m_Target += move;*/
}

void CPlayer::Collision()
{
	if (move.y < 0.0f) 
	{
		BOOL flag = false;
		FLOAT len = 0.0f;
		D3DXVECTOR3 pos, up;
		up = D3DXVECTOR3(0, 10, 0);
		D3DXVec3TransformCoord(&pos, &m_trans.GetPosition(), jimenwInv);
		D3DXIntersect(jimen, &(pos + up), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &flag, NULL, NULL, NULL, &len, NULL, NULL);
		if (flag)
		{
			if (up.y >= len)
			{
				float y = up.y - len;

				m_trans.AddPosition(D3DXVECTOR3(0, y, 0));
				m_Target.y += y;
				move.y = 0;
			}
		}
	}
}
