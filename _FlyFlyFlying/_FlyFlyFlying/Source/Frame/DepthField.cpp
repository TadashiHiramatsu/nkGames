#include"DepthField.h"
#include"DXCommon.h"
#include"haba.h"
#include"GraphicsDevice.h"

extern Frame::CRenderTarget RT;
extern Frame::CRenderTarget RT2;


DepthField::DepthField()
{

}

DepthField::~DepthField()
{

}

void DepthField::Create()
{
	int w = WINDOW_WIDTH;
	int h = WINDOW_HEIGHT;

	Near = 0.2f;
	Far = 1.0f;


	m_downSamplingRenderTarget[0].Create(w >> 1, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
	m_downSamplingRenderTarget[1].Create(w >> 1, h >> 1, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
	m_downSamplingRenderTarget[2].Create(w >> 2, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
	m_downSamplingRenderTarget[3].Create(w >> 2, h >> 2, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。

	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		graphicsDevice(),
		"shader\\DepthField.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_pEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		abort();
	}

	fullscreen.Initialize();
}

void DepthField::UpdateWeight(float dis)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		m_weights[i] = expf(-0.5f*(float)(i*i) / dis);
		if (0 == i)
		{
			total += m_weights[i];
		}
		else
		{
			total += 2.0f*m_weights[i];
		}
	}
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		m_weights[i] /= total;
	}
}

void DepthField::Render()
{
	UpdateWeight(25.0f);
	LPDIRECT3DSURFACE9 rt;
	LPDIRECT3DSURFACE9 depth;
	(*graphicsDevice()).GetRenderTarget(0, &rt);
	(*graphicsDevice()).GetDepthStencilSurface(&depth);
	//XBlur
	{
		(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[0].GetSurfaceDx());
		(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[0].GetDepthSurfaceDx());
		(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		m_pEffect->SetTechnique("XBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float size[2] = {
			static_cast<float>(RT.GetWidth()),
			static_cast<float>(RT.GetHeight())
		};
		float offset[] = {
			16.0f / static_cast<float>(RT.GetWidth()),
			0.0f
		};
		m_pEffect->SetValue("g_TexSize", size, sizeof(size));
		m_pEffect->SetValue("g_offset", offset, sizeof(size));
		m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_pEffect->SetTexture("g_blur", RT.GetTexture());
		m_pEffect->CommitChanges();
		fullscreen.DrawPrimitiveOnly();


		m_pEffect->EndPass();
		m_pEffect->End();

	}
	//YBlur
	{
		(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[1].GetSurfaceDx());
		(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[1].GetDepthSurfaceDx());
		(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		m_pEffect->SetTechnique("YBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float size[2] = {
			static_cast<float>(m_downSamplingRenderTarget[0].GetWidth()),
			static_cast<float>(m_downSamplingRenderTarget[0].GetHeight())
		};
		float offset[] = {
			0.0f,
			16.0f / static_cast<float>(m_downSamplingRenderTarget[0].GetHeight()),
		};
		m_pEffect->SetValue("g_TexSize", size, sizeof(size));
		m_pEffect->SetValue("g_offset", offset, sizeof(offset));
		m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_pEffect->SetTexture("g_blur", m_downSamplingRenderTarget[0].GetTexture());
		m_pEffect->CommitChanges();
		fullscreen.DrawPrimitiveOnly();


		m_pEffect->EndPass();
		m_pEffect->End();
	}

	//XBlur2
	{
		(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[2].GetSurfaceDx());
		(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[2].GetDepthSurfaceDx());
		(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		m_pEffect->SetTechnique("XBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float size[2] = {
			static_cast<float>(m_downSamplingRenderTarget[1].GetWidth()),
			static_cast<float>(m_downSamplingRenderTarget[1].GetHeight())
		};
		float offset[] = {
			16.0f / static_cast<float>(m_downSamplingRenderTarget[1].GetWidth()),
			0.0f
		};
		m_pEffect->SetValue("g_TexSize", size, sizeof(size));
		m_pEffect->SetValue("g_offset", offset, sizeof(offset));
		m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_pEffect->SetTexture("g_blur", m_downSamplingRenderTarget[1].GetTexture());
		m_pEffect->CommitChanges();
		fullscreen.DrawPrimitiveOnly();


		m_pEffect->EndPass();
		m_pEffect->End();

	}
	//YBlur2
	{
		(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[3].GetSurfaceDx());
		(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[3].GetDepthSurfaceDx());
		(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		m_pEffect->SetTechnique("YBlur");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		float size[2] = {
			static_cast<float>(m_downSamplingRenderTarget[2].GetWidth()),
			static_cast<float>(m_downSamplingRenderTarget[2].GetHeight())
		};
		float offset[] = {
			0.0f,
			16.0f / static_cast<float>(m_downSamplingRenderTarget[2].GetHeight()),
		};
		m_pEffect->SetValue("g_TexSize", size, sizeof(size));
		m_pEffect->SetValue("g_offset", offset, sizeof(offset));
		m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_pEffect->SetTexture("g_blur", m_downSamplingRenderTarget[2].GetTexture());
		m_pEffect->CommitChanges();
		fullscreen.DrawPrimitiveOnly();


		m_pEffect->EndPass();
		m_pEffect->End();
	}

	//被写界深度
	{
		
		(*graphicsDevice()).SetRenderTarget(0, rt);
		(*graphicsDevice()).SetDepthStencilSurface(depth);

		m_pEffect->SetTechnique("DepthField");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);
		m_pEffect->SetTexture("g_tex0", RT.GetTexture());//そのまま
		m_pEffect->SetTexture("g_tex1", RT2.GetTexture());//Z値
		m_pEffect->SetTexture("g_tex2", m_downSamplingRenderTarget[1].GetTexture());//ぼけ
		m_pEffect->SetTexture("g_tex3", m_downSamplingRenderTarget[3].GetTexture());//大ボケ
		m_pEffect->SetFloat("g_Near", Near);
		m_pEffect->SetFloat("g_Far", Far);
		m_pEffect->SetFloat("g_Len", Far - Near);
		m_pEffect->CommitChanges();

		fullscreen.DrawPrimitiveOnly();


		m_pEffect->EndPass();
		m_pEffect->End();

		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	}
}
