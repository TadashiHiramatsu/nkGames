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

		//�C���X�^���X�̎擾
		static CSceneManager& GetInstance()
		{
			static CSceneManager instance;
			return instance;
		}

		//���������Ăяo����GameObjectManager��������
		void ChangeScene(IScene* nextscene);

	private:
		IScene* nowScene;
	};
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}
}