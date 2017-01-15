#include "SceneManager.h"

#include"TitleScene.h"
#include"MainScene.h"
#include"ClearScene.h"
#include"OverScene.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
}

void CSceneManager::InitializeScene()
{
	SINSTANCE(CSceneManager)->Add(new CTitleScene("Title"));
	SINSTANCE(CSceneManager)->Add(new CMainScene("main"));
	SINSTANCE(CSceneManager)->Add(new CClearScene("Clear"));
	SINSTANCE(CSceneManager)->Add(new COverScene("Over"));
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
	m_scenes[m_nowScene]->Initialize();
}

void CSceneManager::UpdateScene()
{
	m_scenes[m_nowScene]->Update();
}

void CSceneManager::DrawScene()
{
	m_scenes[m_nowScene]->Draw();
}

void CSceneManager::ChangeScene(const int& key)
{
	m_nowScene = key;
	m_scenes[m_nowScene]->Initialize();
}

CSceneManager* CSceneManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSceneManager();
	}
	return m_pInstance;
}