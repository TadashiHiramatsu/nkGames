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
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
