/***********************************************************************/
/*! @file  SceneManager.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "SceneManager.h"

#include"TitleScene.h"
#include"MainScene.h"
#include"ClearScene.h"
#include"OverScene.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pAdd 
 *  @retval void
 */
/***********************************************************************/
void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneManager::InitializeScene()
{
	SINSTANCE(CSceneManager)->Add(new CTitleScene("Title"));
	SINSTANCE(CSceneManager)->Add(new CMainScene("main"));
	SINSTANCE(CSceneManager)->Add(new CClearScene("Clear"));
	SINSTANCE(CSceneManager)->Add(new COverScene("Over"));
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
	m_scenes[m_nowScene]->Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneManager::UpdateScene()
{
	m_scenes[m_nowScene]->Update();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CSceneManager::DrawScene()
{
	m_scenes[m_nowScene]->Draw();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] key 
 *  @retval void
 */
/***********************************************************************/
void CSceneManager::ChangeScene(const int& key)
{
	m_nowScene = key;
	m_scenes[m_nowScene]->Initialize();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval CSceneManager* 
 */
/***********************************************************************/
CSceneManager* CSceneManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSceneManager();
	}
	return m_pInstance;
}