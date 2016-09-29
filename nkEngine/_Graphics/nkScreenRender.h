#pragma once

#include"nkRenderTarget.h"
#include"nkSprite.h"
#include"PostEffect\nkAntiAliasing.h"

namespace nkEngine
{
	class CScreenRender
	{
	public:

		//������
		void Init(const SInitParam& initParam);
		
		//�X�V
		void Update();

		//�`��
		void Render();

		//���C�������_�[�^�[�Q�b�g���擾
		CRenderTarget& GetMainRenderTarget()
		{
			return m_rtMain;
		}

		//�C���X�^���X�擾
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}
		
	private:

		//�R���X�g���N�^
		CScreenRender();
		
		//�f�X�g���N�^
		~CScreenRender();

	private:
		CRenderTarget m_rtBackBuffer;
		CRenderTarget m_rtMain;

		CAntiAliasing m_AntiAliasing;
	};

	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
}