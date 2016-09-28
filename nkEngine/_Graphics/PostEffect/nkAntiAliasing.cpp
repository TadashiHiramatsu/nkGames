#include"nkEngine/nkstdafx.h"
#include"nkAntiAliasing.h"

namespace nkEngine
{
	CAntiAliasing::CAntiAliasing():
		m_effect(nullptr),
		m_isEnable(false)
	{
	}

	CAntiAliasing::~CAntiAliasing()
	{
	}

	void CAntiAliasing::Init()
	{
		m_isEnable = true;
		m_effect = EffectManager().LoadEffect("AntiAliasing.fx");

		full.Load();
		full.Init();
	}

	void CAntiAliasing::Render(const CTexture* tex)
	{	
		if (m_isEnable)
		{
			//ƒAƒ“ƒ`—LŒø
			float texSize[] = {
				Engine().GetFrameW(),
				Engine().GetFrameH()
			};
			m_effect->SetTechnique("FXAA");
			m_effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			m_effect->BeginPass(0);
			m_effect->SetTexture("g_Texture", tex->GetTextureDX());
			m_effect->SetValue("g_TexSize", texSize, sizeof(texSize));
			m_effect->CommitChanges();
			
			full.DrawPrimitiveOnly();
			
			m_effect->EndPass();
			m_effect->End();

		}
	}

	void CAntiAliasing::Release()
	{
	}
}