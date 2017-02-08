/***********************************************************************/
/*! @file  TitleScene.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "TitleScene.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTitleScene::Initialize()
{
	this->CreateSprite();
	this->m_pTitleBack = new CTitleBack();
	this->m_pTitleBack->Initialize();
	this->m_pTitleCursor = new CTitleCursor();
	this->m_pTitleCursor->Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTitleScene::Update()
{
	this->m_pTitleBack->Update();
	this->m_pTitleCursor->Update();
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::MAIN);
	}
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CTitleScene::Draw()
{
	this->m_pTitleBack->Draw(this->m_pSprite);
	this->m_pTitleCursor->Draw(this->m_pSprite);

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval HRESULT 
 */
/***********************************************************************/
HRESULT CTitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(graphicsDevice(), &m_pSprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}
