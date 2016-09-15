#include"nkEngine/nkstdafx.h"
#include"nkShadow.h"


namespace nkEngine
{
	CShadowMap::CShadowMap():
		m_isActive(false),
		m_near(1.0f),
		m_far(1000.0f),
		m_Aspect(1.0f),
		m_shadowAreaW(50.0f),
		m_shadowAreaH(50.0f),
		m_camera(nullptr),
		m_calcLightViewFunc(enCalcLightViewFunc_PositionTarget),
		m_vLTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXMatrixIdentity(&m_mLView);
		m_vLPosition = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
		m_vLDirection = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	}

	CShadowMap::~CShadowMap()
	{
		Release();
	}

	void CShadowMap::Create(int w, int h)
	{
		Release();

		m_near = 1.0f;
		m_far = 100.0f;

		m_shadowMapRT.Create(w, h, 1, D3DFMT_G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		m_isActive = true;

		m_Aspect = (float)w / (float)h;

		D3DXMatrixOrthoLH(&m_mProj, m_shadowAreaW * m_Aspect, m_shadowAreaH, m_near, m_far);
	
		m_blur.Init(w, h, *m_shadowMapRT.GetTexture());
	}

	void CShadowMap::Update()
	{
		if (m_isActive)
		{
			if (m_calcLightViewFunc == enCalcLightViewFunc_PositionTarget)
			{
				//ライトの視点と注視点で計算
				m_vLDirection = m_vLTarget - m_vLPosition;
				D3DXVec3Normalize(&m_vLDirection, &m_vLDirection);
			}

			//ライトビュープロジェクション行列を作成
			D3DXVECTOR3 vLUp;
			float t = fabsf(D3DXVec3Dot(&m_vLDirection, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
			if (fabsf((t - 1.0f)) < 0.00001f)
			{
				vLUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				vLUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}

			//ライトから見たビュー行列を作成
			D3DXVECTOR3 target;

			target = m_vLPosition + m_vLDirection;

			D3DXMatrixLookAtLH(&m_mLView, &m_vLPosition, &target, &vLUp);
		
			D3DXMatrixOrthoLH(&m_mProj, m_shadowAreaW * m_Aspect, m_shadowAreaH, m_near, m_far);
		
			m_mLViewProj = m_mLView * m_mProj;
		}
	}

	void CShadowMap::Render()
	{
		if (m_isActive)
		{
			IDirect3DDevice9* Device = Engine().GetDevice();

			LPDIRECT3DSURFACE9 BackBuffer;
			LPDIRECT3DSURFACE9 BackDepthBuffer;
			Device->GetRenderTarget(0, &BackBuffer);
			Device->GetDepthStencilSurface(&BackDepthBuffer);

			Device->SetRenderTarget(0, m_shadowMapRT.GetSurface());
			Device->SetDepthStencilSurface(m_shadowMapRT.GetDepthSurface());

			Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

			for (auto model : m_shadowModels) {
				model->DrawToShadowMap();
			}

			Device->SetRenderTarget(0, BackBuffer);
			Device->SetDepthStencilSurface(BackDepthBuffer);

			m_shadowModels.clear();

			m_blur.Render();
		}
	}

	void CShadowMap::Release()
	{
		m_shadowMapRT.Release();
	}

	void CShadowMap::Entry(CModelRender* model)
	{
		m_shadowModels.push_back(model);
	}
}