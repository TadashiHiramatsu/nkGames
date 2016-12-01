#include"nkEngine/nkstdafx.h"
#include"nkSceneManager.h"

namespace nkEngine
{
	CSceneManager::CSceneManager():
		nowScene(nullptr)
	{
	}

	CSceneManager::~CSceneManager()
	{

	}

	void CSceneManager::ChangeScene(IScene* nextscene)
	{
		SAFE_DELETE(nowScene);
		nowScene = nextscene;

		//�o�^����Ă���Q�[���I�u�W�F�N�g��S�폜
		GameObjectManager().AllDelete();

		//�V���h�E�ݒ�
		Shadow().Create(nowScene->GetGraphicsConfig().ShadowConfig);

		nowScene->Start();
	}
}