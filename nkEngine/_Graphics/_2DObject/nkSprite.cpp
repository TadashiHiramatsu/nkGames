/**
 * @file	_Graphics\_2DObject\nkSprite.cpp
 *
 * �X�v���C�g�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkSprite.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/10
	 */
	Sprite::Sprite() :
		RectUV_(D3DXVECTOR4(0, 0, 1, 1)),
		Color_(D3DXVECTOR4(1, 1, 1, 1))
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	Sprite::~Sprite()
	{
	}

	/**
	 * �ǂݍ���.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 *
	 * @param	filePath	The file path to load.
	 */
	void Sprite::Load(const char * filePath)
	{
		//�e�N�X�`���̃��[�h
		Texture_.Load(filePath);

		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("Sprite.fx");
	}

	/**
	 * ������.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Start()
	{
		//�p�[�e�B�N���̏�����
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
		short ib[] =
		{
			0,1,2,3
		};
		//�v���~�e�B�u�̍쐬
		Primitive_.Create(
			Primitive::TriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vb,
			4,
			IndexFormat16,
			ib
		);
	}

	/**
	 * �`��.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Render()
	{
		//�r���[�v���W�F�N�V�����s��̌v�Z
		D3DXMATRIX viewProj;
		D3DXMatrixMultiply(&viewProj, &Camera_->GetViewMatrix(), &Camera_->GetProjectionMatrix());

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		Effect_->SetTechnique("Sprite");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		Effect_->SetValue("g_mWorld", &Transform_->WorldMatrix_, sizeof(D3DXMATRIX));
		Effect_->SetValue("g_mViewProj", &viewProj, sizeof(D3DXMATRIX));

		Effect_->SetTexture("g_Texture", Texture_.GetTexture());

		Effect_->SetValue("g_RectUV", &RectUV_, sizeof(RectUV_));
		Effect_->SetValue("g_Color", &Color_, sizeof(Color_));
		
		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();
	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/11
	 */
	void Sprite::Release()
	{
		Texture_.Release();
	}

}// namespace nkEngine