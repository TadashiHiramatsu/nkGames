#include"stdafx.h"
#include"CArmoredCore.h"

CArmoredCore::CArmoredCore()
{

}

CArmoredCore::~CArmoredCore()
{

}

void CArmoredCore::Init()
{
	m_Leg.Init();
	m_Leg.LoadModel("prototype_3_Leg.X");
	m_Leg.GetACModel()->SetTransform(m_Tranceform);
	m_Leg.GetACModel()->SetLight(m_Light);
	m_Leg.GetACModel()->SetCamera(m_Camera);

	m_Core.Init();
	m_Core.LoadModel("prototype_3_Core.X");
	m_Core.GetACModel()->SetLight(m_Light);
	m_Core.GetACModel()->SetCamera(m_Camera);
	m_Core.GetACModel()->SetParentMatrix(m_Leg.GetMatrix("Core"));

	m_Head.Init();
	m_Head.LoadModel("prototype_3_Head.X");
	m_Head.GetACModel()->SetLight(m_Light);
	m_Head.GetACModel()->SetCamera(m_Camera);
	m_Head.GetACModel()->SetParentMatrix(m_Core.GetMatrix("Head"));

	m_LeftArm.Init();
	m_LeftArm.LoadModel("prototype_3_LeftArm.X");
	m_LeftArm.GetACModel()->SetLight(m_Light);
	m_LeftArm.GetACModel()->SetCamera(m_Camera);
	m_LeftArm.GetACModel()->SetParentMatrix(m_Core.GetMatrix("LeftArm"));

	m_RightArm.Init();
	m_RightArm.LoadModel("prototype_3_RightArm.X");
	m_RightArm.GetACModel()->SetLight(m_Light);
	m_RightArm.GetACModel()->SetCamera(m_Camera);
	m_RightArm.GetACModel()->SetParentMatrix(m_Core.GetMatrix("RightArm"));
}

void CArmoredCore::Update()
{
	m_Leg.Update();
	m_Core.Update();
	m_Head.Update();
	m_LeftArm.Update();
	m_RightArm.Update();
}

void CArmoredCore::Render()
{
	m_Leg.Render();
	m_Core.Render();
	m_Head.Render();
	m_LeftArm.Render();
	m_RightArm.Render();
}

void CArmoredCore::Release()
{
	m_Leg.Release();
	m_Core.Release();
	m_Head.Release();
	m_LeftArm.Release();
	m_RightArm.Release();
}
