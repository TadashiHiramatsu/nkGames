//レンダーターゲット
#ifndef _NKRENDERTARGET_
#define _NKRENDERTARGET_

#include"nkTexture.h"

namespace nkEngine
{
	class CRenderTarget
	{
	public:
		//コンストラクタ
		CRenderTarget();
		//デストラクタ
		~CRenderTarget();
		//レンダーターゲットの作成
		void Create(
		int sizeW,
			int sizeH,
			int mipLevel,
			D3DFORMAT colorFormat,
			D3DFORMAT depthStencilFormat,
			D3DMULTISAMPLE_TYPE multiSampleType,
			int multiSampleQuality
		);
		//レンダリングターゲットの破棄
		void Release();
		//テクスチャの取得
		const CTexture* GetTexture() const
		{
			return &m_texture;
		}
		//レンダリングターゲットの幅を取得
		int GetSizeW()
		{
			return m_sizeW;
		}
		//レンダリングターゲットの高さを取得
		int GetSizeH()
		{
			return m_sizeH;
		}
		//深度バッファ用のサーフェイスを取得
		IDirect3DSurface9* GetDepthSurface()
		{
			return m_DepthSurface;
		}
		//サーフェイスを取得
		IDirect3DSurface9* GetSurface()
		{
			return m_Surface;
		}
		//深度バッファ用のサーフェイスをセット
		void SetDepthSurface(IDirect3DSurface9* depthsurface)
		{
			m_DepthSurface = depthsurface;
		}
		//サーフェイスをセット
		void SetSurface(IDirect3DSurface9* surface)
		{
			m_Surface = surface;
		}
	private:
		//レンダリングターゲットの幅
		int m_sizeW;
		//レンダリングターゲットの高さ
		int m_sizeH;
		//深度バッファ用のサーフェイス
		IDirect3DSurface9* m_DepthSurface;
		//サーフェイス
		IDirect3DSurface9* m_Surface;
		//書き込みさきテクスチャ
		IDirect3DTexture9* m_TextureDX;
		//テクスチャ
		CTexture m_texture;
	};
}

#endif // !_NKRENDERTARGET_