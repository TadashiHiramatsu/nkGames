/**
 * @file _GameObject\nkGameObjectManager.cpp
 *
 * ゲームオブジェクトマネージャクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	 * ゲームオブジェクトマネージャの初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 *
	 * @param prioValue The prio value.
	 */
	void CGameObjectManager::StartGOM(int prioValue)
	{
		//優先度の最高値を設定
		GOPriorityMax_ = prioValue;

		//リサイズ
		GameObjectArray_.resize(GOPriorityMax_);
		DeleteObjectArray_.resize(GOPriorityMax_);
	}

	/**
	 * 初期化.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::Start()
	{
		for (GameObjectListT objList : GameObjectArray_)
		{
			for (IGameObject* obj : objList)
			{
				obj->StartWrapper();
			}
		}
	}

	/**
	 * Updateの前に呼ばれる更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::PreUpdate()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList)
			{
				obj->PreUpdateWrapper();
			}
		}
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::Update()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList) 
			{
				obj->UpdateWrapper();
			}
		}
	}

	/**
	 * Updateの後に呼ばれる更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::PostUpdate()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList) 
			{
				obj->PostUpdateWrapper();
			}
		}
	}

	/**
	 * Renderの前に呼ばれる描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::PreRender()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList) 
			{
				obj->PreRenderWrapper();
			}
		}
	}

	/**
	 * 描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::Render()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList)
			{
				obj->RenderWrapper();
			}
		}
	}

	/**
	 * ポストエフェクトの後に呼ばれる描画.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::PostRender()
	{
		for (GameObjectListT objList : GameObjectArray_) 
		{
			for (IGameObject* obj : objList) 
			{
				obj->PostRenderWrapper();
			}
		}
	}

	/**
	 * deleteObjectArrayに登録されているGameObjectを削除する.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::Delete()
	{
		//デリート予定のオブジェクトを全網羅
		for (GameObjectListT& goList : DeleteObjectArray_) 
		{
			for (IGameObject* go : goList) 
			{

				//優先度から取得
				GOPriorityT prio = go->GetPriority();
				GameObjectListT& goExecList = GameObjectArray_.at(prio);

				//取得
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) 
				{
					//削除
					delete (*it);
				}

				goExecList.erase(it);
			}

			goList.clear();
		}

	}

	/**
	 * 全削除SceneManagerに呼ばれる.
	 * isStaticがtrueの場合消されない.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::AllDelete()
	{
		//イテレータ取得
		auto& itList = GameObjectArray_.begin();
		while (itList != GameObjectArray_.end())
		{
			auto& it = itList->begin();
			while (it != itList->end())
			{
				if ((*it)->GetStatic())
				{
					it++;
				}
				else
				{
					it = itList->erase(it);
				}
			}

			//itList->clear();
			itList++;
		}
	}

}// namespace nkEngine