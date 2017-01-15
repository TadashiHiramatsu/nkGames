#include "OverScene.h"


void COverScene::Initialize()
{
	this->CreateSprite();
	this->m_pOverBack = new COverBack();
	this->m_pOverBack->Initialize();
}

void COverScene::Update()
{
	this->m_pOverBack->Update();
}


void COverScene::Draw()
{
	this->m_pOverBack->Draw(this->m_pSprite);
}

HRESULT COverScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
