#pragma once

#include"nkRenderTarget.h"
#include"nkSprite.h"

namespace nkEngine
{
	class COffScreenRender
	{
	public:
		void Init(const SInitParam& initParam);
		void Update();
		void Render();
		static COffScreenRender& GetInstance()
		{
			static COffScreenRender instance;
			return instance;
		}
	private:
		COffScreenRender(){}
		~COffScreenRender(){}
		CRenderTarget m_RenderTarget;
		D3DVIEWPORT9 m_viewport;

		CSprite full;
	};
	static COffScreenRender& OffScreenRender()
	{
		return COffScreenRender::GetInstance();
	}
}