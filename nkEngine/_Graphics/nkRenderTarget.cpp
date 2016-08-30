#include"nkEngine/nkstdafx.h"
#include"nkRenderTarget.h"

namespace nkEngine
{
	CRenderTarget::CRenderTarget():
	m_DepthSurface(nullptr),
		m_Surface(nullptr),
		m_TextureDX(nullptr),
		m_sizeW(0),
		m_sizeH(0)
	{}

	CRenderTarget::~CRenderTarget()
	{
		Release();
	}
	void CRenderTarget::Create(int sizeW, int sizeH, int mipLevel, D3DFORMAT colorFormat, D3DFORMAT depthStencilFormat, D3DMULTISAMPLE_TYPE multiSampleType, int multiSampleQuality)
	{
		Release();
		m_sizeW = sizeW;
		m_sizeH = sizeH;
		
		IDirect3DDevice9* Device = Engine().GetDevice();

		HRESULT hr = Device->CreateDepthStencilSurface(
		    m_sizeW,
			m_sizeH,
			depthStencilFormat,
			multiSampleType,
			multiSampleQuality,
			TRUE,
			&m_DepthSurface,
			NULL);

		D3DCAPS9 caps;
		Device->GetDeviceCaps(&caps);

		NK_ASSERT(SUCCEEDED(hr), "failed CreateDepthStencilSurface");

		//カラーバッファを作成
		hr = Device->CreateTexture(
			m_sizeW,
			m_sizeH,
			mipLevel,
			D3DUSAGE_RENDERTARGET,
			s_cast<D3DFORMAT>(colorFormat),
			D3DPOOL_DEFAULT,
			&m_TextureDX,
			NULL);

		NK_ASSERT(SUCCEEDED(hr), "Failed CreateTexture");

		hr = m_TextureDX->GetSurfaceLevel(0, &m_Surface);
		
		NK_ASSERT(SUCCEEDED(hr), "Failed GetSurfaceLevel");

		m_texture.SetTextureDX(m_TextureDX);
	}
	void CRenderTarget::Release()
	{
		SAFE_RELEASE(m_TextureDX);
		SAFE_RELEASE(m_DepthSurface);
		SAFE_RELEASE(m_Surface);
	}
}