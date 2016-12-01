#include"nkEngine/nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{
	CGameObjectManager::CGameObjectManager()
	{
	}

	CGameObjectManager::~CGameObjectManager()
	{

	}

	void CGameObjectManager::StartGOM(int _prioValue)
	{
		goPriority = _prioValue;
		gameObjectArray.resize(goPriority);
		deleteObjectArray.resize(goPriority);
	}

	void CGameObjectManager::Start()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
	}

	void CGameObjectManager::PreUpdate()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->PreUpdateWrapper();
			}
		}
	}

	void CGameObjectManager::Update()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
	}

	void CGameObjectManager::PostUpdate()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->PostUpdateWrapper();
			}
		}
	}

	void CGameObjectManager::PreRender()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->PreRenderWrapper();
			}
		}
	}

	void CGameObjectManager::Render()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->RenderWrapper();
			}
		}
	}

	void CGameObjectManager::PostRender()
	{
		for (GameObjectList objList : gameObjectArray) {
			for (IGameObject* obj : objList) {
				obj->PostRenderWrapper();
			}
		}
	}

	void CGameObjectManager::Delete()
	{
		//�f���[�g�\��̃I�u�W�F�N�g��S�ԗ�
		for (GameObjectList& goList : deleteObjectArray) {
			for (IGameObject* go : goList) {
				//�D��x����擾
				GOPriority prio = go->GetPriority();
				GameObjectList& goExecList = gameObjectArray.at(prio);
				//�擾
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) {
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

	void CGameObjectManager::AllDelete()
	{
		for (GameObjectList objList : gameObjectArray) {
			objList.clear();
		}
	}
}