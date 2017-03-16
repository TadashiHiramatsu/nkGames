/**
 * @file _Graphics\_PostEffect\nkPostEffect.cpp
 *
 * �|�X�g�G�t�F�N�g�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkPostEffect.h"

namespace nkEngine
{

	/**
	 * �쐬.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param config The configuration.
	 */
	void PostEffect::Create(const GraphicsConfigS& config)
	{

		//�A���`�G�C���A�V���O�̏�����
		AntiAliasing_.Create(config.AntiAliasingConfig_);
		//�u���[���̏�����
		Bloom_.Create(config.BloomConfig_);

		//���_�o�b�t�@�̍쐬
		static SShapeVertex_PT vb[] = 
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
		//�C���f�b�N�X�o�b�t�@�̍쐬
		static unsigned short ib[] = 
		{
			0,1,2,3
		};
		//�v���~�e�B�u�̏�����
		Primitive_.Create(
			Primitive::TypeE::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormatE::IndexFormat16,
			ib
		);

	}

	/**
	 * �`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void PostEffect::Render()
	{
	
		//�u���[���̕`��
		Bloom_.Render(this);
		//�A���`�G�C���A�X�̕`��
		AntiAliasing_.Render(this);

	}

	/**
	 * �t���X�N���[���̕`��.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void PostEffect::RenderFullScreen()
	{
		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());
	
	}

}// namespace nkEngine