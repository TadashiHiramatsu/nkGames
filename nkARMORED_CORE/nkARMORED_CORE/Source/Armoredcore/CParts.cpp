#include"stdafx.h"
#include"CParts.h"

CParts::CParts()
{

}

CParts::~CParts()
{

}

void CParts::Init()
{
	m_ACModel.SetTransform(&m_Transform);
	m_ACModel.SetShadowCasterFlag(true);
	m_ACModel.SetShadowReceiverFlag(true);
}

void CParts::Update()
{
	m_ACModel.Update();
}

void CParts::Render()
{
	m_ACModel.Render();
}

void CParts::Release()
{
	m_ACModel.Release();
}

void CParts::LoadModel(const char* filepass)
{
	m_ACModel.Load(filepass, &m_Animation);
}
