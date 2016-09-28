#pragma once

#include"nkRenderTarget.h"
#include"nkSprite.h"
#include"PostEffect\nkAntiAliasing.h"

namespace nkEngine
{
	class COffScreenRender
	{
	public:

		//������
		void Init(const SInitParam& initParam);
		
		//�X�V
		void Update();

		//�`��
		void Render();

		//�C���X�^���X�擾
		inline static COffScreenRender& GetInstance()
		{
			static COffScreenRender instance;
			return instance;
		}
		
	private:

		//�R���X�g���N�^
		COffScreenRender();
		
		//�f�X�g���N�^
		~COffScreenRender();

	private:

		CRenderTarget m_RenderTarget;
		D3DVIEWPORT9 m_viewport;

		CAntiAliasing m_AntiAliasing;

		CSprite full;
	};

	inline static COffScreenRender& OffScreenRender()
	{
		return COffScreenRender::GetInstance();
	}
}