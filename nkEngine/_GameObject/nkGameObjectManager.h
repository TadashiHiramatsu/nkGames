#pragma once
#include"nkGameObject.h"

namespace nkEngine
{
	class CGameObjectManager
	{
	public:
		CGameObjectManager();
		~CGameObjectManager();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̏�����
		void Init();

		//�Q�[���I�u�W�F�N�g�̍X�V
		void Update();
		//�Q�[���I�u�W�F�N�g�̕`��
		void Render();

		void AddGameObject(shared_ptr<CGameObject> go);
	private:
		map<unsigned int, shared_ptr<CGameObject>> m_mGameObject;
		list<shared_ptr<CGameObject>> m_lGameObject;
	};
}