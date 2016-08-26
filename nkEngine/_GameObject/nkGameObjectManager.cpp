#include"nkEngine/nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{
	CGameObjectManager::CGameObjectManager()
	{
		m_lGameObject.clear();
		m_mGameObject.clear();
	}

	CGameObjectManager::~CGameObjectManager()
	{

	}

	void CGameObjectManager::Init()
	{

	}



	void CGameObjectManager::Update()
	{
		m_lGameObject.sort();
		for(auto game : m_lGameObject)
		{
			game->Update();
		}
	}

	void CGameObjectManager::Render()
	{
		for (auto game : m_lGameObject)
		{
			game->Render();
		}
	}

	void CGameObjectManager::AddGameObject(shared_ptr<CGameObject> go)
	{
		unsigned int hash = CHash::MakeHash(typeid(go).name());
		m_mGameObject.insert(map<unsigned int, shared_ptr<CGameObject>>::value_type(hash, go));
		m_lGameObject.push_back(go);
	}
}