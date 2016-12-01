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

		//登録されているゲームオブジェクトを全削除
		GameObjectManager().AllDelete();

		//シャドウ設定
		Shadow().Create(nowScene->GetGraphicsConfig().ShadowConfig);

		nowScene->Start();
	}
}