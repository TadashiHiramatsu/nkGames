#include"nkEngine/nkstdafx.h"
#include"nkBlur.h"

namespace nkEngine
{
	CBlur::CBlur() :
		m_srcTexture(nullptr)
	{

	}

	CBlur::~CBlur()
	{

	}

	void CBlur::Init(int w, int h, const CTexture & srcTexture)
	{
		m_srcTexture = &srcTexture;

		D3DSURFACE_DESC desc;
		m_srcTexture->GetTextureDX()->GetLevelDesc(0, &desc);

		m_srcTexWH[0] = w;
		m_srcTexWH[1] = h;

		int  size[2][2]
		{
			{ w >> 1,h },
			{w >> 1,h >> 1},
		};

		for (int i = 0; i < 2; i++)
		{
			m_rt[i].Create(size[i][0], size[i][1], 1, desc.Format, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
		}

		m_fullscreen.Init();

		m_Effect = EffectManager().LoadEffect("Blur.fx");
	}

	void CBlur::Render()
	{
		if (m_srcTexture != nullptr)
		{

			IDirect3DDevice9* Device = Engine().GetDevice();

			LPDIRECT3DSURFACE9 BackBuffer;
			LPDIRECT3DSURFACE9 BackDepthBuffer;

			Device->GetRenderTarget(0, &BackBuffer);
			Device->GetDepthStencilSurface(&BackDepthBuffer);

			//Xブラー。
			{
				Device->SetRenderTarget(0, m_rt[0].GetSurface());
				Device->SetDepthStencilSurface(m_rt[0].GetDepthSurface());

				float size[2] = {
					s_cast<float>(m_srcTexWH[0]),
					s_cast<float>(m_srcTexWH[1])
				};
				m_Effect->SetTechnique("XBlur");
				m_Effect->Begin(0, D3DXFX_DONOTSAVESTATE);
				m_Effect->BeginPass(0);
				m_Effect->SetTexture("g_blur", m_srcTexture->GetTextureDX());
				m_Effect->SetValue("g_texSize", size, sizeof(size));
				m_Effect->CommitChanges();

				m_fullscreen.DrawPrimitiveOnly();

				m_Effect->EndPass();
				m_Effect->End();
			}
			//Yブラー。
			{
				Device->SetRenderTarget(0, m_rt[1].GetSurface());
				Device->SetDepthStencilSurface(m_rt[1].GetDepthSurface());


				float size[2] = {
					s_cast<float>(m_rt[0].GetSizeW()),
					s_cast<float>(m_rt[0].GetSizeH())
				};
				m_Effect->SetTechnique("YBlur");
				m_Effect->Begin(0, D3DXFX_DONOTSAVESTATE);
				m_Effect->BeginPass(0);
				m_Effect->SetTexture("g_tex", m_rt[0].GetTexture()->GetTextureDX());
				m_Effect->SetValue("g_texSize", size, sizeof(size));
				m_Effect->CommitChanges();

				m_fullscreen.DrawPrimitiveOnly();


				m_Effect->EndPass();
				m_Effect->End();
			}

			Device->SetRenderTarget(0, BackBuffer);
			Device->SetDepthStencilSurface(BackDepthBuffer);
		}
	}
}