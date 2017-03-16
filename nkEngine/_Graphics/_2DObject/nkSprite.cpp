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
		//�v���~�e�B�u�̏�����

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
	 * @author	HiramatsuTadashi
	 * @date	2017/01/06
	 */
	void Sprite::Render()
	{

		//���[���h�r���[�v���W�F�N�V�����s��̌v�Z
		Matrix mWVP = Matrix::Identity;
		mWVP.Mul(Transform_->WorldMatrix_, Camera_->GetViewMatrix());
		mWVP.Mul(mWVP, Camera_->GetProjectionMatrix());

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�A���t�@�u�����f�B���O���s��
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// ���ߏ������s��
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		// �������������s��
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		//�e�N�j�b�N��ݒ�.
		Effect_->SetTechnique("Sprite");

		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);

		//���[���h�r���[�v���W�F�N�V�����s���ݒ�.
		Effect_->SetMatrix("g_mWVP", &mWVP);

		//�e�N�X�`����ݒ�.
		Effect_->SetTexture("g_Texture", &Texture_);

		//UV��ݒ�.
		Effect_->SetValue("g_RectUV", &RectUV_, sizeof(RectUV_));

		//�F��ݒ�.
		Effect_->SetValue("g_Color", &Color_, sizeof(Color_));
		
		Effect_->CommitChanges();

		Device->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		Effect_->EndPass();
		Effect_->End();

		//���ɖ߂�
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

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