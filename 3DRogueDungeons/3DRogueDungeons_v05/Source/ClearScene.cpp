/***********************************************************************/
/*! @file  ClearScene.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "ClearScene.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CClearScene::Initialize()
{
	this->CreateSprite();
	this->m_pClearBack = new CClearBack();
	this->m_pClearBack->Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CClearScene::Update()
{
	this->m_pClearBack->Update();
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CClearScene::Draw()
{
	this->m_pClearBack->Draw(this->m_pSprite);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CClearScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
