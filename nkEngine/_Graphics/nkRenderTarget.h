//�����_�[�^�[�Q�b�g
#ifndef _NKRENDERTARGET_
#define _NKRENDERTARGET_

#include"nkTexture.h"

namespace nkEngine
{
	class CRenderTarget
	{
	public:
		//�R���X�g���N�^
		CRenderTarget();
		//�f�X�g���N�^
		~CRenderTarget();
		//�����_�[�^�[�Q�b�g�̍쐬
		void Create(
		int sizeW,
			int sizeH,
			int mipLevel,
			D3DFORMAT colorFormat,
			D3DFORMAT depthStencilFormat,
			D3DMULTISAMPLE_TYPE multiSampleType,
			int multiSampleQuality
		);
		//�����_�����O�^�[�Q�b�g�̔j��
		void Release();
		//�e�N�X�`���̎擾
		const CTexture* GetTexture() const
		{
			return &m_texture;
		}
		//�����_�����O�^�[�Q�b�g�̕����擾
		int GetSizeW()
		{
			return m_sizeW;
		}
		//�����_�����O�^�[�Q�b�g�̍������擾
		int GetSizeH()
		{
			return m_sizeH;
		}
		//�[�x�o�b�t�@�p�̃T�[�t�F�C�X���擾
		IDirect3DSurface9* GetDepthSurface()
		{
			return m_DepthSurface;
		}
		//�T�[�t�F�C�X���擾
		IDirect3DSurface9* GetSurface()
		{
			return m_Surface;
		}
		//�[�x�o�b�t�@�p�̃T�[�t�F�C�X���Z�b�g
		void SetDepthSurface(IDirect3DSurface9* depthsurface)
		{
			m_DepthSurface = depthsurface;
		}
		//�T�[�t�F�C�X���Z�b�g
		void SetSurface(IDirect3DSurface9* surface)
		{
			m_Surface = surface;
		}
	private:
		//�����_�����O�^�[�Q�b�g�̕�
		int m_sizeW;
		//�����_�����O�^�[�Q�b�g�̍���
		int m_sizeH;
		//�[�x�o�b�t�@�p�̃T�[�t�F�C�X
		IDirect3DSurface9* m_DepthSurface;
		//�T�[�t�F�C�X
		IDirect3DSurface9* m_Surface;
		//�������݂����e�N�X�`��
		IDirect3DTexture9* m_TextureDX;
		//�e�N�X�`��
		CTexture m_texture;
	};
}

#endif // !_NKRENDERTARGET_