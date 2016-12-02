#pragma once

#include"nkScene.h"

namespace nkEngine
{
	class CSceneManager
	{
	private:
		//コンストラクタ
		CSceneManager();
		//デストラクタ
		~CSceneManager();
	public:

		//インスタンスの取得
		static CSceneManager& GetInstance()
		{
			static CSceneManager instance;
			return instance;
		}

		//初期化を呼び出してGameObjectManagerを初期化
		template <class T>
		void ChangeScene()
		{
			SAFE_DELETE(nowScene);

			T* scene = new T;
			nowScene = scene;

			//登録されているゲームオブジェクトを全削除
			GameObjectManager().AllDelete();

			//シャドウ設定
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