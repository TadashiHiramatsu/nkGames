#pragma once

#include"nkScene.h"

namespace nkEngine
{
	class CSceneManager
	{
	public:
		void Init();
		void UpdateScene();
		void RenderScene();
		void ChangeScene(CScene* nextscene);
		static CSceneManager& GetInstance()
		{
			static CSceneManager instance;
			return instance;
		}
	private:
		CSceneManager();
		~CSceneManager();
	private:
		CScene* m_nowscene;
	};
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}
}