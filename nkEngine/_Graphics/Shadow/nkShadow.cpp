#include"nkEngine/nkstdafx.h"
#include"nkShadow.h"


namespace nkEngine
{
	//無名空間
	//ここに書かれたものはこのファイルでしか扱えないグローバルになる
	namespace {
		const float shadowAreaTable[CShadowMap::MAX_SHADOW_MAP][2] =
		{
			{ 20.0f, 20.0f },
			{ 45.0f, 45.0f },
			{ 120.0f, 120.0f },
		};
	}
	CShadowMap::CShadowMap():
		m_isEnable(false),
		m_near(1.0f),
		m_far(1000.0f),
		m_Aspect(1.0f),
		m_calcLightViewFunc(enCalcLightViewFunc_PositionTarget),
		m_vLightTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXMatrixIdentity(&m_mLightView);
		m_vLightPosition = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
		m_vLightDirection = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		
		for (int i = 0; i < MAX_SHADOW_MAP; i++) {
			m_shadowAreaW[i] = shadowAreaTable[i][0];
			m_shadowAreaH[i] = shadowAreaTable[i][1];
		}
	}

	CShadowMap::~CShadowMap()
	{
		Release();
	}

	void CShadowMap::Create(const SShadowConfig& config)
	{
		Release();

		m_near = config.Near;
		m_far = config.Fur;
		m_isEnable = config.isEnable;
		int w = config.ShadowMapW;
		int h = config.ShadowMapH;

		m_Aspect = (float)w / (float)h;

		int wh[MAX_SHADOW_MAP][2] = {
			{ w, h },
			{ w >> 1, h >> 1 },
			{ w >> 1, h >> 1 },
		};

		for (int i = 0; i < MAX_SHADOW_MAP; i++)
		{
			m_shadowMapRT[i].Create(wh[i][0], wh[i][1], 1, D3DFMT_G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
			m_blur[i].Init(w, h, *m_shadowMapRT[i].GetTexture());
		}
	}

	void CShadowMap::Update()
	{
		if (m_isEnable)
		{
			if (m_calcLightViewFunc == enCalcLightViewFunc_PositionTarget)
			{
				//ライトの視点と注視点で計算
				m_vLightDirection = m_vLightTarget - m_vLightPosition;
				D3DXVec3Normalize(&m_vLightDirection, &m_vLightDirection);
			}

			//ライトビュープロジェクション行列を作成
			D3DXVECTOR3 vLightUp;
			float t = fabsf(D3DXVec3Dot(&m_vLightDirection, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
			if (fabsf((t - 1.0f)) < 0.00001f)
			{
				vLightUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				vLightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}

			//ライトから見たビュー行列を作成
			D3DXVECTOR3 vLightTarget;

			vLightTarget = m_vLightPosition + m_vLightDirection;

			D3DXMatrixLookAtLH(&m_mLightView, &m_vLightPosition, &vLightTarget, &vLightUp);
		
			for (int i = 0; i < MAX_SHADOW_MAP; i++) 
			{
				D3DXMatrixOrthoLH(&m_mProjection, m_shadowAreaW[i] * m_Aspect,m_shadowAreaH[i],m_near,m_far);
				D3DXMatrixMultiply(&m_shadowReceiverParam.mLightViewProjection[i], &m_mLightView, &m_mProjection);
			}

			m_shadowReceiverParam.vsmFlag = true;
			m_shadowReceiverParam.numShadowMap = MAX_SHADOW_MAP;

		}
	}

	void CShadowMap::Render()
	{
		if (m_isEnable)
		{
			IDirect3DDevice9* Device = Engine().GetDevice();

			//バックアップ作成
			LPDIRECT3DSURFACE9 BackBuffer;
			LPDIRECT3DSURFACE9 BackDepthBuffer;
			Device->GetRenderTarget(0, &BackBuffer);
			Device->GetDepthStencilSurface(&BackDepthBuffer);

			for (int i = 0; i < MAX_SHADOW_MAP; i++)
			{
				Device->SetRenderTarget(0, m_shadowMapRT[i].GetSurface());
				Device->SetDepthStencilSurface(m_shadowMapRT[i].GetDepthSurface());
				Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

				m_mLightViewProjection = m_shadowReceiverParam.mLightViewProjection[i];
				for (auto model : m_shadowModels) {
					model->RenderToShadowMap();
				}
				m_blur[i].Render();
			}

			Device->SetRenderTarget(0, BackBuffer);
			Device->SetDepthStencilSurface(BackDepthBuffer);

			m_shadowModels.clear();
		}
	}

	void CShadowMap::Release()
	{
		for (int i = 0; i < MAX_SHADOW_MAP; i++)
		{
			m_shadowMapRT[i].Release();
		}
	}

	void CShadowMap::Entry(CModelRender* model)
	{
		m_shadowModels.push_back(model);
	}
}