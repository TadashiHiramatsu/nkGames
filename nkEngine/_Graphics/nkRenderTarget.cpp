/**
 * @file _Graphics\nkRenderTarget.cpp
 *
 * レンダーターゲットクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRenderTarget.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	RenderTarget::RenderTarget() :
	    D3DDepthSurface_(nullptr),
		D3DSurface_(nullptr),
		D3DTextureDX_(nullptr),
		SizeW_(0),
		SizeH_(0)
	{
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	RenderTarget::~RenderTarget()
	{
		Release();
	}

	/**
	 * レンダーターゲットの作成.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param sizeW				 The size w.
	 * @param sizeH				 The size h.
	 * @param mipLevel			 The mip level.
	 * @param colorFormat		 The color format.
	 * @param depthStencilFormat The depth stencil format.
	 * @param multiSampleType    Type of the multi sample.
	 * @param multiSampleQuality The multi sample quality.
	 */
	void RenderTarget::Create(int sizeW, int sizeH, int mipLevel, D3DFORMAT colorFormat, D3DFORMAT depthStencilFormat, D3DMULTISAMPLE_TYPE multiSampleType, int multiSampleQuality)
	{
		//解放
		Release();
	
		//サイズをコピー
		SizeW_ = sizeW;
		SizeH_ = sizeH;
		
		//デバイスの取得
		IDirect3DDevice9* Device = Engine().GetDevice();

		//深度サーフェスの作成
		HRESULT hr = Device->CreateDepthStencilSurface(
		    SizeW_,
			SizeH_,
			depthStencilFormat,
			multiSampleType,
			multiSampleQuality,
			TRUE,
			&D3DDepthSurface_,
			NULL
		);
		NK_ASSERT(SUCCEEDED(hr), "深度サーフェス作成失敗");

		//カラーバッファを作成
		hr = Device->CreateTexture(
			SizeW_,
			SizeH_,
			mipLevel,
			D3DUSAGE_RENDERTARGET,
			s_cast<D3DFORMAT>(colorFormat),
			D3DPOOL_DEFAULT,
			&D3DTextureDX_,
			NULL
		);
		NK_ASSERT(SUCCEEDED(hr), "カラーバッファ作成失敗");

		hr = D3DTextureDX_->GetSurfaceLevel(0, &D3DSurface_);
		NK_ASSERT(SUCCEEDED(hr), "Failed GetSurfaceLevel");

		Texture_.SetTextureDX(D3DTextureDX_);
	}

	/**
	 * 解放.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void RenderTarget::Release()
	{
		SAFE_RELEASE(D3DTextureDX_);
		SAFE_RELEASE(D3DDepthSurface_);
		SAFE_RELEASE(D3DSurface_);
	}

}// namespace nkEngine