/***********************************************************************/
/*! @file  OverScene.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "OverScene.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void COverScene::Initialize()
{
	this->CreateSprite();
	this->m_pOverBack = new COverBack();
	this->m_pOverBack->Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void COverScene::Update()
{
	this->m_pOverBack->Update();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void COverScene::Draw()
{
	this->m_pOverBack->Draw(this->m_pSprite);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT COverScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
