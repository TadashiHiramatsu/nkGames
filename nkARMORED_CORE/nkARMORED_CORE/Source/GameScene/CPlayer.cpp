#include"stdafx.h"
#include"CPlayer.h"
#include"CGameCamera.h"

CPlayer::CPlayer():
	m_TargetLen(30)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_anim = new CAnimation();
	m_model.Init("UnityChan_SD.x",m_anim);
	m_model.SetCamera(g_camera.GetCamera());
	m_model.SetTransform(&m_trans);
	m_model.SetLight(&m_light);
	m_model.SetShadowCasterFlag(true);
	m_model.SetShadowReceiverFlag(true);

	m_normal.Load("utc_nomal.tga");
	m_model.SetNormalMap(&m_normal);

	m_spec.Load("utc_spec.tga");
	m_model.SetSpecMap(&m_spec);

	m_anim->SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationStand;
	PlayAnimation(currentAnimSetNo);

	Shadow().SetLightPosition(D3DXVECTOR3(3.5f, 3.5f, 3.5f));
	Shadow().SetLightTarget(m_trans.GetPosition());
	Shadow().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));
	m_light.SetDiffuseLightColor(4, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));
	m_light.SetDiffuseLightColor(5, D3DXVECTOR4(0.8f, 0.8f, 0.8f, 5.0f));

	m_Target = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Target *= m_TargetLen;
}

void CPlayer::Update()
{
	Rotation();
	Move();
	m_model.Update();
	m_anim->Update(1.0f / 60.0f);
	g_camera.SetPlayerTarget(m_Target);
	g_camera.SetPlayerPosition(m_trans.GetPosition());

	Shadow().SetLightPosition(m_trans.GetPosition() + D3DXVECTOR3(3.5f, 3.5f, 3.5f));
	Shadow().SetLightTarget(m_trans.GetPosition());
}

void CPlayer::Render()
{
	m_model.Draw();
}

void CPlayer::Release()
{
	m_model.Release();
}

void CPlayer::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimSetNo != animNo) {
		//別のアニメーション
		m_anim->PlayAnimation(animNo, 0.1f);
		currentAnimSetNo = animNo;
	}
}

void CPlayer::Rotation()
{
	//プレイヤーの視点から注視点のベクトルを作成
	D3DXVECTOR3 m_toTarget = m_Target - m_trans.GetPosition();
	//回転させてる
	D3DXMATRIX tmp;
	D3DXMatrixIdentity(&tmp);

	if (XInput().GetStickR_X() <= -1)
	{
		D3DXMatrixRotationY(&tmp, -0.05);
	}
	if (XInput().GetStickR_X() >= 1)
	{
		D3DXMatrixRotationY(&tmp, 0.05);
	}

	//回転
	D3DXVec3TransformCoord(&m_toTarget, &m_toTarget, &tmp);
	//回転した注視点
	D3DXVec3Normalize(&m_toTarget, &m_toTarget);
	m_Target = m_toTarget * m_TargetLen + m_trans.GetPosition();
	
	//進行方向と横方向を作成
	m_direction_Z = g_camera.GetDirection();
	D3DXVec3Normalize(&m_direction_Z, &m_direction_Z);
	D3DXVec3Cross(&m_direction_X, &m_direction_Z, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));


	//逆な気がするけどできてる謎
	{
		float angle = acos(D3DXVec3Dot(&-m_direction_X, &D3DXVECTOR3(1.0f, 0.0f, 0.0f)));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &m_direction_X, &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		D3DXQUATERNION mRotation = m_trans.GetRotation();
		D3DXQuaternionRotationAxis(&mRotation, &axis, angle);
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
	}
	if (XInput().GetStickL_Y() >= 1)
	{
		move += m_direction_Z;
	}
	D3DXVec3Normalize(&move, &move);
	m_trans.AddPosition(move * Speed);
}
