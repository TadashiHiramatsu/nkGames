/**
 * @file _GameObject\nkGameObjectManager.h
 *
 * �Q�[���I�u�W�F�N�g�}�l�[�W���N���X�̒�`.
 */
#pragma once

#include"nkGameObject.h"

namespace nkEngine
{

	/**
	 * �Q�[���I�u�W�F�N�g�}�l�[�W��.
	 * ���̃N���X�ɃQ�[���I�u�W�F�N�g���p�������N���X��o�^����� 
	 * �����ŏ������A�X�V�A�`����Ă�ł����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	class CGameObjectManager : Noncopyable
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		CGameObjectManager()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		~CGameObjectManager()
		{
		}

	public:

		/**
		 * �C���X�^���X�̎擾.
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
		 * �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param prioValue �D��x�̍ō��l.
		 */
		void StartGOM(int prioValue);

	public:

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Start();

		/**
		 * Update�̑O�ɌĂ΂��X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PreUpdate();

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Update();

		/**
		 * Update�̌�ɌĂ΂��X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PostUpdate();

		/**
		 * Render�̑O�ɌĂ΂��`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PreRender();

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Render();

		/**
		 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void PostRender();

		/**
		 * deleteObjectArray�ɓo�^����Ă���GameObject���폜����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void Delete();

	public:

		/**
		 * GameObject�o�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @tparam TGO IGameObject���p�������N���X.
		 * @param prio �D��x.
		 *
		 * @return Null if it fails, else a pointer to a T.
		 */
		template<class TGO>
		TGO* NewGameObject(GOPriorityT prio)
		{
			//�Q�[���I�u�W�F�N�g�쐬
			TGO* newGO = new TGO;

			//�R���X�g���N�^�AStart�Ԃ̏�����
			newGO->Awake();

			//�D��x�ݒ�
			newGO->Priority_ = prio;

			//List�ɒǉ�
			GameObjectArray_.at(prio).push_back(newGO);

			return newGO;
		}

		/**
		 * GameObjectManager����폜����GameObject��o�^����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 *
		 * @param [in,out] go If non-null, the go.
		 */
		void DeleteGameObject(IGameObject* go)
		{
			//�폜List�ɒǉ�
			DeleteObjectArray_.at(go->GetPriority()).push_back(go);
		}

		/**
		 * �S�폜SceneManager�ɌĂ΂��.
		 * isStatic��true�̏ꍇ������Ȃ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/10
		 */
		void AllDelete();
		
	private:

		/** 1�D��x��1List. */
		typedef list<IGameObject*> GameObjectListT;
		/** �o�^����Ă���GameObject. */
		vector<GameObjectListT> GameObjectArray_;
		/** �폜����GameObject. */
		vector<GameObjectListT> DeleteObjectArray_;
		/** �D��x�̍ő�l��ݒ�. */
		GOPriorityT GOPriorityMax_;
		/** �D��x�̍ő�l. */
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
	 * �Q�[���I�u�W�F�N�g�쐬�o�^.
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
	 * �Q�[���I�u�W�F�N�g�폜�o�^.
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