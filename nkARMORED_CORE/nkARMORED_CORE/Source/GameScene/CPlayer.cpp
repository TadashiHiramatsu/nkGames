#include"stdafx.h"
#include"CPlayer.h"
#include"CGameCamera.h"

CPlayer::CPlayer()
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
	normal.Load("utc_nomal.tga");
	m_model.SetNormalMap(&normal);

	m_anim->SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationStand;
	PlayAnimation(currentAnimSetNo);


	Shadow().SetLightPosition(D3DXVECTOR3(3.5f, 3.5f, 3.5f));
	Shadow().SetLightTarget(m_trans.GetPosition());
	Shadow().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
}

void CPlayer::Update()
{
	m_model.Update();
	//PlayAnimation(AnimationStand);
	m_anim->Update(1.0f / 60.0f);
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
