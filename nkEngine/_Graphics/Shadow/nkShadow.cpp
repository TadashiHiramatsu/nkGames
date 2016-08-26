#include"nkEngine/nkstdafx.h"
#include"nkShadow.h"


namespace nkEngine
{

	void CShadowMap::Create(int w, int h,bool Active)
	{
		this->h = h;
		this->w = w;
		m_isActive = Active;
		m_shadowMapRT.Create(this->w, this->h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		m_near = 1.0f;
		m_far = 100.0f;

		m_shadowModels.clear();

		LPD3DXBUFFER  compileErrorBuffer = NULL;
		HRESULT hr = D3DXCreateEffectFromFile(
			Engine().GetDevice(),
			"shader\\shadow.fx",
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
	}


	void CShadowMap::Draw(D3DXMATRIX proj)
	{
		if (m_isActive)
		{

			Engine().GetDevice()->GetViewport(&m_viewport);
			Engine().GetDevice()->GetRenderTarget(0, &m_Backbuffer);
			Engine().GetDevice()->GetDepthStencilSurface(&m_BackZ);

			Engine().GetDevice()->SetRenderTarget(0, m_shadowMapRT.GetSurface());
			Engine().GetDevice()->SetDepthStencilSurface(m_shadowMapRT.GetDepthSurface());

			Engine().GetDevice()->Clear(
				0,
				NULL,
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				1.0f,
				0);

			D3DVIEWPORT9 viewport = { 0, 0, (DWORD)w, (DWORD)h, 0.0f, 1.0f };
			Engine().GetDevice()->SetViewport(&viewport);
			Engine().GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			float aspect;
			aspect = (float)viewport.Width / (float)viewport.Height;
			D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DXToRadian(120.0f), aspect, m_near, m_far);

			CreateLight();

			int size = m_shadowModels.size();
			
			D3DXMatrixMultiply(&m_VPMatrix, &m_lvMatrix, &m_projMatrix);

			for (int idx = 0; idx < size; idx++)
			{
				
			}
			Engine().GetDevice()->SetRenderTarget(0, m_Backbuffer);
			Engine().GetDevice()->SetDepthStencilSurface(m_BackZ);
			Engine().GetDevice()->SetViewport(&m_viewport);
			Engine().GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
	}

	void CShadowMap::CreateLight()
	{
		D3DXVECTOR3 lightUp;
		float t = fabsf(D3DXVec3Dot(&m_lightDirection, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
		if (fabsf((t - 1.0f)) < 0.00001f)
		{
			lightUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		D3DXVECTOR3 target;
		D3DXVec3Add(&target, &m_lightPosition, &m_lightDirection);
		D3DXMatrixLookAtLH(&m_lvMatrix, &m_lightPosition, &target, &lightUp);
		D3DXMatrixMultiply(&m_LVPMatrix, &m_lvMatrix, &m_projMatrix);
	}

	void CShadowMap::Release()
	{
		m_shadowMapRT.Delete();
		if (m_pEffect != nullptr) {
			//m_pEffect->Release();
			m_pEffect = nullptr;
		}
	}

	void CShadowMap::Entry(CModelRender* model)
	{
		m_shadowModels.push_back(model);
	}

}