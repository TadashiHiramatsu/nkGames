#include"nkEngine/nkstdafx.h"
#include"nkSceneManager.h"

namespace nkEngine
{
	CSceneManager::CSceneManager():
		m_nowscene(nullptr)
	{
	}

	CSceneManager::~CSceneManager()
	{

	}

	void CSceneManager::Init()
	{

	}

	void CSceneManager::UpdateScene()
	{
		m_nowscene->Update();
	}

	void CSceneManager::RenderScene()
	{
		m_nowscene->Render();
	}

	void CSceneManager::ChangeScene(CScene* nextscene)
	{
		if (m_nowscene != nullptr)
		{
			SAFE_DELETE(m_nowscene);
		}
		m_nowscene = nextscene;
		m_nowscene->Init();
	}
}