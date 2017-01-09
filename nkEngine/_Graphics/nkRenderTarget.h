/**
 * @file _Graphics\nkRenderTarget.h
 *
 * レンダーターゲットクラスの定義.
 */
#pragma once

#include"nkTexture.h"

namespace nkEngine
{

	/**
	 * レンダーターゲットクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class RenderTarget
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		RenderTarget();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~RenderTarget();

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
		void Create(
		int sizeW,
			int sizeH,
			int mipLevel,
			D3DFORMAT colorFormat,
			D3DFORMAT depthStencilFormat,
			D3DMULTISAMPLE_TYPE multiSampleType,
			int multiSampleQuality
		);

		/**
		 * 解放.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * テクスチャの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the texture.
		 */
		IDirect3DTexture9* GetTextureDX() const
		{
			return Texture_.GetTexture();
		}

		/**
		 * テクスチャクラスの取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the texture dx.
		 */
		const Texture* GetTexture() const
		{
			return &Texture_;
		}

		/**
		 * レンダリングターゲットの幅を取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size w.
		 */
		int GetSizeW()
		{
			return SizeW_;
		}

		/**
		 * レンダリングターゲットの高さを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size h.
		 */
		int GetSizeH()
		{
			return SizeH_;
		}

		/**
		 * 深度バッファ用のサーフェイスを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the depth surface.
		 */
		IDirect3DSurface9* GetDepthSurface()
		{
			return D3DDepthSurface_;
		}

		/**
		 * サーフェイスを取得.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the surface.
		 */
		IDirect3DSurface9* GetSurface()
		{
			return D3DSurface_;
		}

		/**
		 * 深度バッファ用のサーフェイスをセット.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] depthsurface If non-null, the depthsurface.
		 */
		void SetDepthSurface(IDirect3DSurface9* depthsurface)
		{
			D3DDepthSurface_ = depthsurface;
		}

		/**
		 * サーフェイスをセット.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param [in,out] surface If non-null, the surface.
		 */
		void SetSurface(IDirect3DSurface9* surface)
		{
			D3DSurface_ = surface;
		}

	private:

		/** レンダリングターゲットの横幅. */
		int SizeW_;
		/** レンダリングターゲットの高さ. */
		int SizeH_;
		/** 深度バッファ用のサーフェイス. */
		IDirect3DSurface9* D3DDepthSurface_;
		/** サーフェイス. */
		IDirect3DSurface9* D3DSurface_;
		/** カラーバッファ. */
		IDirect3DTexture9* D3DTextureDX_;
		/** テクスチャ. */
		Texture Texture_;

	};

}// namespace nkEngine