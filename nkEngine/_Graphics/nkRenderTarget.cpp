/**
 * @file _Graphics\nkRenderTarget.cpp
 *
 * �����_�[�^�[�Q�b�g�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkRenderTarget.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
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
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	RenderTarget::~RenderTarget()
	{
		Release();
	}

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
	void RenderTarget::Create(int sizeW, int sizeH, int mipLevel, D3DFORMAT colorFormat, D3DFORMAT depthStencilFormat, D3DMULTISAMPLE_TYPE multiSampleType, int multiSampleQuality)
	{
		//���
		Release();
	
		//�T�C�Y���R�s�[
		SizeW_ = sizeW;
		SizeH_ = sizeH;
		
		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�[�x�T�[�t�F�X�̍쐬
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
		NK_ASSERT(SUCCEEDED(hr), "�[�x�T�[�t�F�X�쐬���s");

		//�J���[�o�b�t�@���쐬
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
		NK_ASSERT(SUCCEEDED(hr), "�J���[�o�b�t�@�쐬���s");

		hr = D3DTextureDX_->GetSurfaceLevel(0, &D3DSurface_);
		NK_ASSERT(SUCCEEDED(hr), "Failed GetSurfaceLevel");

		Texture_.SetTextureDX(D3DTextureDX_);
	}

	/**
	 * ���.
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