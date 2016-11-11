#pragma once

#include"nkScene.h"

namespace nkEngine
{
	class CSceneManager
	{
	private:
		//�R���X�g���N�^
		CSceneManager();
		//�f�X�g���N�^
		~CSceneManager();
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
		CScene* m_nowscene;
	};
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}
}