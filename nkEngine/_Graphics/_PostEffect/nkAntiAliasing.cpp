/**
 * @file _Graphics\_PostEffect\nkAntiAliasing.cpp
 *
 * �A���`�G�C���A�V���O�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkAntiAliasing.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	AntiAliasing::AntiAliasing() :
		Effect_(nullptr),
		isEnable_(false)
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	AntiAliasing::~AntiAliasing()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void AntiAliasing::Init()
	{

		isEnable_ = true;
		
		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("AntiAliasing.fx");

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

	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void AntiAliasing::Render()
	{	
		if (isEnable_)
		{
			//�A���`�L��
			
			int w = Engine().GetFrameW();
			int h = Engine().GetFrameH();

			float texSize[2] =
			{
				w,
				h,
			};

			Effect_->SetTechnique("FXAA");

			Effect_->Begin(0, D3DXFX_DONOTSAVESTATE);
			Effect_->BeginPass(0);

			Effect_->SetTexture("g_Texture", ScreenRender().GetMainRenderTarget().GetTextureDX());
			Effect_->SetValue("g_TexSize", texSize, sizeof(texSize));
			
			Effect_->CommitChanges();
			
			Engine().GetDevice()->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
			Engine().GetDevice()->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
			Engine().GetDevice()->SetVertexDeclaration(Primitive_.GetVertexDecl());
			Engine().GetDevice()->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

			Effect_->EndPass();
			Effect_->End();

		}

	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void AntiAliasing::Release()
	{
	}

}// namespace nkEngine