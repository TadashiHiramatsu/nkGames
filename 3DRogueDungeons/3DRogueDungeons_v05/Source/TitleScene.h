/***********************************************************************/
/*! @file  TitleScene.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"IncludeManagers.h"

#include"Scene.h"
#include"SceneManager.h"

#include"TitleCursor.h"
#include"TitleBack.h"

class CSceneManager;

class CTitleScene :public CScene
{
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] name 
	 *  @retval  
	 */
	/***********************************************************************/
	CTitleScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	HRESULT CreateSprite();	///<スプライト生成関数
private:
	LPD3DXSPRITE m_pSprite;	///<スプライト
	CTitleCursor* m_pTitleCursor;
	CTitleBack* m_pTitleBack;
};