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
		void ChangeScene(IScene* nextscene);

	private:
		IScene* nowScene;
	};
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}
}