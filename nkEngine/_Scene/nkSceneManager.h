/**
 * @file	_Scene\nkSceneManager.h
 *
 * �V�[���}�l�[�W���N���X�̒�`.
 */
#pragma once

#include"nkScene.h"

namespace nkEngine
{

	/**
	 * �V�[���}�l�[�W���N���X.
	 * �V���O���g���N���X.
	 * ���̃N���X��IScene�N���X���p�������N���X��o�^����.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CSceneManager
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CSceneManager();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CSceneManager();

	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CSceneManager& GetInstance()
		{
			static CSceneManager instance;
			return instance;
		}

		/**
		 * IScene�N���X�p���N���X�̏��������Ăяo���� 
		 * GameObjectManager�N���X��������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @tparam	TScene	IScene�N���X���p�������N���X.
		 */
		template <class TScene>
		void ChangeScene()
		{
			SAFE_DELETE(NowScene_);

			//�V�[���N���X�̍쐬
			T* scene = new T;

			//�i�E�V�[���ɐݒ�
			NowScene_ = scene;

			//�o�^����Ă���Q�[���I�u�W�F�N�g��S�폜
			GameObjectManager().AllDelete();

			//�V���h�E�N���X�̏�����
			Shadow().Create(NowScene_->GetGraphicsConfig().ShadowConfig);

			//�V�[���N���X�̏�����
			NowScene_->Start();
		}

	private:

		/** The now scene. */
		IScene* NowScene_;

	};

	/**
	 * �V�[���}�l�[�W���[�̎擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a CSceneManager.
	 */
	inline CSceneManager& SceneManager()
	{
		return CSceneManager::GetInstance();
	}

}// namespace nkEngine