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
		m_nowscene->Init();
		Shadow().Create(m_nowscene->GetGraphicsConfig().ShadowConfig);
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
		SAFE_DELETE(m_nowscene);
		m_nowscene = nextscene;
		Init();
	}
}