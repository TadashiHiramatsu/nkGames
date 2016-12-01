#pragma once

#include"_PostEffect\nkAntiAliasing.h"
#include"_PostEffect\nkBloom.h"

namespace nkEngine
{
	class CScreenRender
	{
	private:

		//�R���X�g���N�^
		CScreenRender();
		//�f�X�g���N�^
		~CScreenRender();

	public:

		//�C���X�^���X�擾
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}

		//������
		void Start(const SInitParam& initParam);

		void Loop();

		//���C�������_�[�^�[�Q�b�g���擾
		CRenderTarget& GetMainRenderTarget()
		{
			return m_rtMain;
		}

	private:
		CRenderTarget m_rtBackBuffer;
		CRenderTarget m_rtMain;

		CAntiAliasing m_AntiAliasing;
		CBloom m_Bloom;
	};

	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
}