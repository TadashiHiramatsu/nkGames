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
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CGameObjectManager::CGameObjectManager()
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CGameObjectManager::~CGameObjectManager()
	{

	}

	/**
	 * Starts a gom.
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
	 * Starts this object.
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
	 * Pre update.
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
	 * Updates this object.
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
	 * Posts the update.
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
	 * Pre render.
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
	 * Renders this object.
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
	 * Posts the render.
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
	 * Deletes this object.
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
					//解放
					(*it)->Release();
					//削除
					delete (*it);
				}

				goExecList.erase(it);
			}

			goList.clear();
		}

	}

	/**
	 * All delete.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::AllDelete()
	{
		//イテレータ取得
		auto itList = GameObjectArray_.begin();
		while (itList != GameObjectArray_.end())
		{
			itList->clear();
			itList++;
		}
	}

}// namespace nkEngine