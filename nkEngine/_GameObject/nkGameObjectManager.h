/**
 * @file _GameObject\nkGameObjectManager.h
 *
 * ゲームオブジェクトマネージャクラスの定義.
 */
#pragma once

#include"nkGameObject.h"

namespace nkEngine
{

	/**
	 * ゲームオブジェクトマネージャ.
	 * このクラスにゲームオブジェクトを継承したクラスを登録すると 
	 * 自動で初期化、更新、描画を呼んでくれる.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class CGameObjectManager : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		CGameObjectManager()
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~CGameObjectManager()
		{
		}

	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @return The instance.
		 */
		static CGameObjectManager& GetInstance()
		{
			static CGameObjectManager instance;
			return instance;
		}

	public:

		/**
		 * ゲームオブジェクトマネージャの初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param prioValue 優先度の最高値.
		 */
		void StartGOM(int prioValue);

	public:

		/**
		 * 初期化.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Start();

		/**
		 * Updateの前に呼ばれる更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PreUpdate();

		/**
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * Updateの後に呼ばれる更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PostUpdate();

		/**
		 * Renderの前に呼ばれる描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PreRender();

		/**
		 * 描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Render();

		/**
		 * ポストエフェクトの後に呼ばれる描画.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PostRender();

		/**
		 * deleteObjectArrayに登録されているGameObjectを削除する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Delete();

	public:

		/**
		 * GameObject登録.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @tparam TGO IGameObjectを継承したクラス.
		 * @param prio 優先度.
		 *
		 * @return Null if it fails, else a pointer to a T.
		 */
		template<class TGO>
		TGO* NewGameObject(GOPriorityT prio)
		{
			//ゲームオブジェクト作成
			TGO* newGO = new TGO;

			//コンストラクタ、Start間の初期化
			newGO->Awake();

			//優先度設定
			newGO->Priority_ = prio;

			//Listに追加
			GameObjectArray_.at(prio).push_back(newGO);

			return newGO;
		}

		/**
		 * GameObjectManagerから削除するGameObjectを登録する.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] go If non-null, the go.
		 */
		void DeleteGameObject(IGameObject* go)
		{
			//削除Listに追加
			DeleteObjectArray_.at(go->GetPriority()).push_back(go);
		}

		/**
		 * 全削除SceneManagerに呼ばれる.
		 * isStaticがtrueの場合消されない.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void AllDelete();
		
	private:

		/** 1優先度に1List. */
		typedef list<IGameObject*> GameObjectListT;
		/** 登録されているGameObject. */
		vector<GameObjectListT> GameObjectArray_;
		/** 削除するGameObject. */
		vector<GameObjectListT> DeleteObjectArray_;
		/** 優先度の最大値を設定. */
		GOPriorityT GOPriorityMax_;
		/** 優先度の最大値. */
		static const GOPriorityT MAX_Priority = 255;

	};

	/**
	 * Game object manager.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @return A reference to a CGameObjectManager.
	 */
	static CGameObjectManager& GameObjectManager()
	{
		return CGameObjectManager::GetInstance();
	}

	/**
	 * ゲームオブジェクト作成登録.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @tparam TGO Type of the tgo.
	 * @param pori (Optional) The pori.
	 *
	 * @return Null if it fails, else a pointer to a TGO.
	 */
	template<class TGO>
	static TGO* NewGO(int pori = 0)
	{
		return GameObjectManager().NewGameObject<TGO>(pori);
	}

	/**
	 * ゲームオブジェクト削除登録.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param [in,out] go If non-null, the go.
	 */
	static void DeleteGO(IGameObject* go)
	{
		GameObjectManager().DeleteGameObject(go);
	}

}// namespace nkEngine