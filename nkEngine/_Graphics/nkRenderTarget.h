/**
 * @file _Graphics\nkRenderTarget.h
 *
 * �����_�[�^�[�Q�b�g�N���X�̒�`.
 */
#pragma once

#include"nkTexture.h"

namespace nkEngine
{

	/**
	 * �����_�[�^�[�Q�b�g�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class RenderTarget
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		RenderTarget();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~RenderTarget();

		/**
		 * �����_�[�^�[�Q�b�g�̍쐬.
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
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

		/**
		 * �e�N�X�`���̎擾.
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
		 * �e�N�X�`���N���X�̎擾.
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
		 * �����_�����O�^�[�Q�b�g�̕����擾.
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
		 * �����_�����O�^�[�Q�b�g�̍������擾.
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
		 * �[�x�o�b�t�@�p�̃T�[�t�F�C�X���擾.
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
		 * �T�[�t�F�C�X���擾.
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
		 * �[�x�o�b�t�@�p�̃T�[�t�F�C�X���Z�b�g.
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
		 * �T�[�t�F�C�X���Z�b�g.
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

		/** �����_�����O�^�[�Q�b�g�̉���. */
		int SizeW_;
		/** �����_�����O�^�[�Q�b�g�̍���. */
		int SizeH_;
		/** �[�x�o�b�t�@�p�̃T�[�t�F�C�X. */
		IDirect3DSurface9* D3DDepthSurface_;
		/** �T�[�t�F�C�X. */
		IDirect3DSurface9* D3DSurface_;
		/** �J���[�o�b�t�@. */
		IDirect3DTexture9* D3DTextureDX_;
		/** �e�N�X�`��. */
		Texture Texture_;

	};

}// namespace nkEngine