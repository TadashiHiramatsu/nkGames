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
	 * �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����.
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
	 * ������.
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
	 * Update�̑O�ɌĂ΂��X�V.
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
	 * �X�V.
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
	 * Update�̌�ɌĂ΂��X�V.
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
	 * Render�̑O�ɌĂ΂��`��.
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
	 * �`��.
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
	 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
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
	 * deleteObjectArray�ɓo�^����Ă���GameObject���폜����.
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
					//�폜
					delete (*it);
				}

				goExecList.erase(it);
			}

			goList.clear();
		}

	}

	/**
	 * �S�폜SceneManager�ɌĂ΂��.
	 * isStatic��true�̏ꍇ������Ȃ�.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	void CGameObjectManager::AllDelete()
	{
		//�C�e���[�^�擾
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