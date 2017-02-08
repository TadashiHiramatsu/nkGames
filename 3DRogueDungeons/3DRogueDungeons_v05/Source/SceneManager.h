/***********************************************************************/
/*! @file  SceneManager.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once
#include <vector>
#include "Scene.h"

class CScene;
enum SCENE { TITLE = 0, MAIN ,CLEAR,OVER};

#define SINSTANCE(p) p::getInstance()

class CSceneManager
{
public:
	void Add(CScene* pAdd);
	void InitializeScene();
	void UpdateScene();
	void DrawScene();
	void ChangeScene(const int& key);
	static CSceneManager* getInstance();
private:
	int m_nowScene;
	vector<CScene*> m_scenes;
	CSceneManager(){}
	static CSceneManager* m_pInstance;
};