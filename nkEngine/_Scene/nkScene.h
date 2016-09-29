#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	//�V�[���̊��N���X
	//���̃N���X���p������
	class CScene
	{
	public:

		//�R���X�g���N�^
		CScene();

		//�f�X�g���N�^
		virtual ~CScene();

		//������
		virtual void Init() = 0;

		//�X�V
		virtual void Update() = 0;
		
		//�`��
		virtual void Render() = 0;
		
		//���
		virtual void Release() = 0;

		//�O���t�B�b�N�R���t�B�O�̎擾
		const SGraphicsConfig& GetGraphicsConfig()
		{
			return m_GraphicsConfig;
		}

	protected:
		SGraphicsConfig m_GraphicsConfig;
	};
}
