#pragma once

#include"nkGameObject.h"

namespace nkEngine
{
	//ゲームオブジェクトマネージャ
	//このクラスにゲームオブジェクトを継承したクラスを登録すると
	//自動で初期化、更新、描画を呼んでくれる
	class CGameObjectManager
	{
	private:

		//コンストラクタ
		CGameObjectManager();
		//デストラクタ
		~CGameObjectManager();

	public:

		//インスタンスの取得
		static CGameObjectManager& GetInstance()
		{
			static CGameObjectManager instance;
			return instance;
		}

	public:

		//ゲームオブジェクトマネージャの初期化
		void StartGOM(int _prioValue);

	public:

		//初期化
		void Start();
		//Updateの前に呼ばれる更新
		void PreUpdate();
		//更新
		void Update();
		//Updateの後に呼ばれる更新
		void PostUpdate();
		//Renderの前に呼ばれる描画
		void PreRender();
		//描画
		void Render();
		//ポストエフェクトの後に呼ばれる描画
		void PostRender();

		//deleteObjectArrayに登録されているGameObjectを削除する
		void Delete();

	public:

		//GameObject登録
		template<class T>
		T* NewGameObject(GOPriority _prio)
		{
			T* newGO = new T;
			newGO->Awake();
			newGO->priority = _prio;
			gameObjectArray.at(_prio).push_back(newGO);
			return newGO;
		}

		//GameObjectManagerから削除するGameObjectを登録する
		void DeleteGameObject(IGameObject* _go)
		{
			deleteObjectArray.at(_go->GetPriority()).push_back(_go);
		}

		//全削除SceneManagerに呼ばれる
		void AllDelete();

	private:
		typedef list<IGameObject*> GameObjectList; //1優先度に1List
		vector<GameObjectList> gameObjectArray; //登録されているGameObject
		vector<GameObjectList> deleteObjectArray; //削除するGameObject
		GOPriority goPriority; //優先度の最大値を設定
		static const GOPriority MAX_Priority = 255; //優先度の最大値
	};

	static CGameObjectManager& GameObjectManager()
	{
		return CGameObjectManager::GetInstance();
	}

	//ゲームオブジェクト作成登録
	template<class T>
	static T* NewGO(int _pori = 0)
	{
		return GameObjectManager().NewGameObject<T>(_pori);
	}

	//ゲームオブジェクト削除登録
	static void DeleteGO(IGameObject* _go)
	{
		GameObjectManager().DeleteGameObject(_go);
	}
}