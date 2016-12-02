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
		template <class T>
		void ChangeScene()
		{
			SAFE_DELETE(nowScene);

			T* scene = new T;
			nowScene = scene;

			//�o�^����Ă���Q�[���I�u�W�F�N�g��S�폜
			GameObjectManager().AllDelete();

			//�V���h�E�ݒ�
			Shadow().Create(nowScene->GetGraphicsConfig().ShadowConfig);

			nowScene->Start();
		}

	private:
		IScene* nowScene;
	};
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}
}