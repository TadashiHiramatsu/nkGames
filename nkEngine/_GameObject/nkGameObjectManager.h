#pragma once
#include"nkGameObject.h"

namespace nkEngine
{
	class CGameObjectManager
	{
	public:
		CGameObjectManager();
		~CGameObjectManager();
		//ゲームオブジェクトマネージャーの初期化
		void Init();

		//ゲームオブジェクトの更新
		void Update();
		//ゲームオブジェクトの描画
		void Render();

		void AddGameObject(shared_ptr<CGameObject> go);
	private:
		map<unsigned int, shared_ptr<CGameObject>> m_mGameObject;
		list<shared_ptr<CGameObject>> m_lGameObject;
	};
}