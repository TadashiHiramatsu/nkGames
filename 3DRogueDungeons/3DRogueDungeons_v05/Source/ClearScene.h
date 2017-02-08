/***********************************************************************/
/*! @file  ClearScene.h
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

#include"ClearBack.h"


class CSceneManager;

class CClearScene :public CScene
{
public:
	/***********************************************************************/
	/*! @brief 
	 * 
	 *  @param[in,out] name 
	 *  @retval  
	 */
	/***********************************************************************/
	CClearScene(const string& name) : CScene(name){ }
	void Initialize();
	void Update();
	void Draw();
	HRESULT CreateSprite();	///<スプライト生成関数
private:
	LPD3DXSPRITE m_pSprite;	///<スプライト
	CClearBack* m_pClearBack;
};