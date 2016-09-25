#include"stdafx.h"
#include"CPlayer.h"
#include"CGameCamera.h"

CPlayer::CPlayer():
	m_TargetLen(30),
	jimen(nullptr)
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

	m_ArmoredCore.SetTranceform(&m_trans);
	m_ArmoredCore.SetLight(&m_light);
	m_ArmoredCore.SetCamera(g_camera.GetCamera());
	m_ArmoredCore.Init();

}

void CPlayer::Update()
{
	Rotation();
	Move();
	Collision();

	g_camera.SetPlayerTarget(m_Target);
	g_camera.SetPlayerPosition(m_trans.GetPosition());

	Shadow().SetLightPosition(D3DXVECTOR3(0.0f, 20.5f, 19.5f) + m_trans.GetPosition());
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
	//回転させてる
	D3DXMATRIX tmp;
	D3DXMatrixIdentity(&tmp);

	static int time[2] = { 0 };
	static float rots = 0.1f;
	if (XInput().GetStickR_X() <= -1)
	{
		time[0]++;
		D3DXMatrixRotationY(&tmp, -rots);
	}
	else
	{
		time[0] = 0;
	}
	if (XInput().GetStickR_X() >= 1)
	{
		time[1]++;
		D3DXMatrixRotationY(&tmp, rots);
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
	D3DXVec3TransformCoord(&m_toTarget, &m_toTarget, &tmp);
	//回転した注視点
	m_toTarget.y = 0;
	D3DXVec3Normalize(&m_toTarget, &m_toTarget);
	m_Target = m_toTarget * m_TargetLen + m_trans.GetPosition();
	m_Target.y = m_trans.GetPosition().y;
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
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static float Speed = 1.0f;
	if(XInput().GetStickL_X() <= -1)
	{ 
		move += m_direction_X;
		m_Target += m_direction_X;
	}
	if (XInput().GetStickL_X() >= 1)
	{
		move -= m_direction_X;
		m_Target -= m_direction_X;
	}
	if (XInput().GetStickL_Y() <= -1)
	{
		move -= m_direction_Z;
		m_Target -= m_direction_Z;
	}
	if (XInput().GetStickL_Y() >= 1)
	{
		move += m_direction_Z;
		m_Target += m_direction_Z;
	}

	D3DXVec3Normalize(&move, &move);

	m_trans.AddPosition(move * Speed);
}

void CPlayer::Collision()
{
	BOOL flag = false;
	FLOAT len = 0.0f;
	D3DXVECTOR3 pos ,up;
	up = D3DXVECTOR3(0,10,0);
	D3DXVec3TransformCoord(&pos, &m_trans.GetPosition() , jimenwInv);
	D3DXIntersect(jimen, &(pos + up), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &flag, NULL, NULL, NULL, &len, NULL, NULL);
	if (flag)
	{
		m_trans.AddPosition(D3DXVECTOR3(0, -(len - up.y), 0));
	}
}
