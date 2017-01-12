/**
 * @file _GameObject\nkGameObjectManager.cpp
 *
 * �Q�[���I�u�W�F�N�g�}�l�[�W���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	CGameObjectManager::CGameObjectManager()
	{
	}

	/**
	 * �f�X�g���N�^.
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
		//�D��x�̍ō��l��ݒ�
		GOPriorityMax_ = prioValue;

		//���T�C�Y
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
		//�f���[�g�\��̃I�u�W�F�N�g��S�ԗ�
		for (GameObjectListT& goList : DeleteObjectArray_) 
		{
			for (IGameObject* go : goList) 
			{

				//�D��x����擾
				GOPriorityT prio = go->GetPriority();
				GameObjectListT& goExecList = GameObjectArray_.at(prio);

				//�擾
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) 
				{
					//���
					(*it)->Release();
					//�폜
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
		//�C�e���[�^�擾
		auto itList = GameObjectArray_.begin();
		while (itList != GameObjectArray_.end())
		{
			itList->clear();
			itList++;
		}
	}

}// namespace nkEngine