/**
 * @file _Graphics\nkBlur.cpp
 *
 * �u���[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkBlur.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Blur::Blur() :
		SrcTexture_(nullptr)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	Blur::~Blur()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param w			 The width.
	 * @param h			 The height.
	 * @param srcTexture Source texture.
	 */
	void Blur::Init(int w, int h, const Texture & srcTexture)
	{
		
		//�\�[�X�e�N�X�`�����R�s�[
		SrcTexture_ = &srcTexture;

		D3DSURFACE_DESC desc;
		SrcTexture_->GetTexture()->GetLevelDesc(0, &desc);

		//�T�C�Y���R�s�[
		SrcTexWH_[0] = w;
		SrcTexWH_[1] = h;

		//�u���[�T�C�Y���쐬
		int  size[2][2]
		{
			{ w >> 1, h     },
			{ w >> 1, h >> 1},
		};

		//�����_�����O�^�[�Q�b�g�̍쐬
		for (int i = 0; i < 2; i++)
		{
			BlurRT_[i].Create(size[i][0], size[i][1], 1, desc.Format, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
		}

		static SShapeVertex_PT vertex[] = 
		{
			{
				-1.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-1.0f, -1.0f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				1.0f, -1.0f, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		};
		static unsigned short index[] =
		{
			0,1,2,3
		};
		
		//�v���~�e�B�u�쐬
		Primitive_.Create(
			Primitive::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vertex,
			4,
			IndexFormat16,
			index
		);

		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("Blur.fx");

	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void Blur::Render()
	{
		if (SrcTexture_ != nullptr)
		{

			//�f�o�C�X�̎擾
			IDirect3DDevice9* Device = Engine().GetDevice();

			//�o�b�N�o�b�t�@�̎擾
			LPDIRECT3DSURFACE9 BackBuffer;
			LPDIRECT3DSURFACE9 BackDepthBuffer;

			Device->GetRenderTarget(0, &BackBuffer);
			Device->GetDepthStencilSurface(&BackDepthBuffer);

			//X�u���[�B
			{
				
				//�����_�����O�^�[�Q�b�g���u���[�ɐݒ�
				Device->SetRenderTarget(0, BlurRT_[0].GetSurface());
				Device->SetDepthStencilSurface(BlurRT_[0].GetDepthSurface());

				float size[2] = {
					s_cast<float>(SrcTexWH_[0]),
					s_cast<float>(SrcTexWH_[1])
				};


				Effect_->SetTechnique("XBlur");

				Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
				Effect_->BeginPass(0);
				
				Effect_->SetTexture("g_blur", SrcTexture_);
				Effect_->SetValue("g_texSize", size, sizeof(size));
				
				Effect_->CommitChanges();

				//�v���~�e�B�u�̕`��
				Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

				Effect_->EndPass();
				Effect_->End();

			}
			//Y�u���[�B
			{

				Device->SetRenderTarget(0, BlurRT_[1].GetSurface());
				Device->SetDepthStencilSurface(BlurRT_[1].GetDepthSurface());


				float size[2] = 
				{
					s_cast<float>(BlurRT_[0].GetSizeW()),
					s_cast<float>(BlurRT_[0].GetSizeH())
				};

				Effect_->SetTechnique("YBlur");

				Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
				Effect_->BeginPass(0);
				
				Effect_->SetTexture("g_tex", BlurRT_[0].GetTexture());
				Effect_->SetValue("g_texSize", size, sizeof(size));
				
				Effect_->CommitChanges();

				Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
				Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
				Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
				Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

				Effect_->EndPass();
				Effect_->End();

			}

			//�o�b�N�o�b�t�@�ɖ߂�
			Device->SetRenderTarget(0, BackBuffer);
			Device->SetDepthStencilSurface(BackDepthBuffer);
		
		}
	}

}// namespace nkEngine