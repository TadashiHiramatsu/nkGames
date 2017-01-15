#include "ClearScene.h"


void CClearScene::Initialize()
{
	this->CreateSprite();
	this->m_pClearBack = new CClearBack();
	this->m_pClearBack->Initialize();
}

void CClearScene::Update()
{
	this->m_pClearBack->Update();
}


void CClearScene::Draw()
{
	this->m_pClearBack->Draw(this->m_pSprite);
}

HRESULT CClearScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
