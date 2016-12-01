#pragma once

#include"nkGameObject.h"

namespace nkEngine
{
	//�Q�[���I�u�W�F�N�g�}�l�[�W��
	//���̃N���X�ɃQ�[���I�u�W�F�N�g���p�������N���X��o�^�����
	//�����ŏ������A�X�V�A�`����Ă�ł����
	class CGameObjectManager
	{
	private:

		//�R���X�g���N�^
		CGameObjectManager();
		//�f�X�g���N�^
		~CGameObjectManager();

	public:

		//�C���X�^���X�̎擾
		static CGameObjectManager& GetInstance()
		{
			static CGameObjectManager instance;
			return instance;
		}

	public:

		//�Q�[���I�u�W�F�N�g�}�l�[�W���̏�����
		void StartGOM(int _prioValue);

	public:

		//������
		void Start();
		//Update�̑O�ɌĂ΂��X�V
		void PreUpdate();
		//�X�V
		void Update();
		//Update�̌�ɌĂ΂��X�V
		void PostUpdate();
		//Render�̑O�ɌĂ΂��`��
		void PreRender();
		//�`��
		void Render();
		//�|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��
		void PostRender();

		//deleteObjectArray�ɓo�^����Ă���GameObject���폜����
		void Delete();

	public:

		//GameObject�o�^
		template<class T>
		T* NewGameObject(GOPriority _prio)
		{
			T* newGO = new T;
			newGO->Awake();
			newGO->priority = _prio;
			gameObjectArray.at(_prio).push_back(newGO);
			return newGO;
		}

		//GameObjectManager����폜����GameObject��o�^����
		void DeleteGameObject(IGameObject* _go)
		{
			deleteObjectArray.at(_go->GetPriority()).push_back(_go);
		}

		//�S�폜SceneManager�ɌĂ΂��
		void AllDelete();

	private:
		typedef list<IGameObject*> GameObjectList; //1�D��x��1List
		vector<GameObjectList> gameObjectArray; //�o�^����Ă���GameObject
		vector<GameObjectList> deleteObjectArray; //�폜����GameObject
		GOPriority goPriority; //�D��x�̍ő�l��ݒ�
		static const GOPriority MAX_Priority = 255; //�D��x�̍ő�l
	};

	static CGameObjectManager& GameObjectManager()
	{
		return CGameObjectManager::GetInstance();
	}

	//�Q�[���I�u�W�F�N�g�쐬�o�^
	template<class T>
	static T* NewGO(int _pori = 0)
	{
		return GameObjectManager().NewGameObject<T>(_pori);
	}

	//�Q�[���I�u�W�F�N�g�폜�o�^
	static void DeleteGO(IGameObject* _go)
	{
		GameObjectManager().DeleteGameObject(_go);
	}
}