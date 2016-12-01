#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	//�V�[���̊��N���X
	//���̃N���X���p������
	class IScene
	{
	public:

		//�R���X�g���N�^
		IScene();
		//�f�X�g���N�^
		virtual ~IScene();

	public:

		//������
		virtual void Start() {}

		//�O���t�B�b�N�R���t�B�O�̎擾
		const SGraphicsConfig& GetGraphicsConfig()
		{
			return m_GraphicsConfig;
		}

	protected:
		SGraphicsConfig m_GraphicsConfig;
	};
}
