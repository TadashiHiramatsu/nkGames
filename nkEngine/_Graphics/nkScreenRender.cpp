/**
 * @file _Graphics\nkScreenRender.cpp
 *
 * �V�[�������_�[�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkScreenRender.h"

namespace nkEngine
{

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CScreenRender::Start()
	{
		//�f�o�C�X�̎擾
		Device_ = Engine().GetDevice();

		//���C�������_�[�^�[�Q�b�g�̍쐬
		MainRT_[0].Create(Engine().GetFrameW(), Engine().GetFrameH(), 1, D3DFMT_A16B16G16R16F, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0);
		MainRT_[1].Create(Engine().GetFrameW(), Engine().GetFrameH(), 1, D3DFMT_A16B16G16R16F, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0);

		//�o�b�N�o�b�t�@�����_�[�^�[�Q�b�g�̍쐬
		LPDIRECT3DSURFACE9 rt, depth;
		Device_->GetRenderTarget(0, &rt);
		Device_->GetDepthStencilSurface(&depth);
		BackBufferRT_.SetSurface(rt);
		BackBufferRT_.SetDepthSurface(depth);

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

		//�G�t�F�N�g�̃��[�h
		Effect_ = EffectManager().LoadEffect("TransformedPrim.fx");

	}

	/**
	 * �O���t�B�b�N�֘A�̏�����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 *
	 * @param config The configuration.
	 */
	void CScreenRender::StartGraphic(const GraphicsConfigS& config)
	{
		//�V���h�E�N���X�̏�����
		Shadow().Create(config.ShadowConfig_);

		//�|�X�g�G�t�F�N�g�̏�����
		PostEffect_.Create(config);
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CScreenRender::Loop()
	{
		//�^�C���̍X�V
		Time().Update();

		//DirectInput�̍X�V
		Input().Update();
		//XInput�̍X�V
		XInput().Update();

		//����������Ă��Ȃ��I�u�W�F�N�g��������
		GameObjectManager().Start();

		//�v�������_�����O�O�̍X�V
		GameObjectManager().PreUpdate();

		//�v�������_�����O
		Shadow().Update(); 

		//�X�V
		GameObjectManager().Update();

		//Update�̌�̍X�V
		GameObjectManager().PostUpdate();

		//�V�[���̊J�n
		Device_->BeginScene();

		//�����_�[�^�[�Q�b�g�����C�������_�[�ɐݒ�
		Device_->SetRenderTarget(0, MainRT_[CurrentMainRT_].GetSurface());
		Device_->SetDepthStencilSurface(MainRT_[CurrentMainRT_].GetDepthSurface());
		Device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//�v�������_�[�̕`��
		Shadow().Render();

		//Render�̑O�̕`��
		GameObjectManager().PreRender();

		//�`��
		GameObjectManager().Render();

		//�|�X�g�G�t�F�N�g�̕`��
		PostEffect_.Render();

		//�|�X�g�G�t�F�N�g�̌�̕`��
		GameObjectManager().PostRender();

		//�o�b�N�o�b�t�@�ɏ�������
		BackBufferRender();

		//�V�[���̏I��
		Device_->EndScene();
		Device_->Present(NULL, NULL, NULL, NULL);

		//�폜�o�^���ꂽGameObject���폜
		GameObjectManager().Delete();
	}

	/**
	 * �o�b�N�o�b�t�@�Ƀ����_�����O.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/16
	 */
	void CScreenRender::BackBufferRender()
	{
		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
		Device_->SetRenderTarget(0, BackBufferRT_.GetSurface());
		Device_->SetDepthStencilSurface(BackBufferRT_.GetDepthSurface());
		Device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//�������܂�Ă��郌���_�����O�^�[�Q�b�g���擾
		RenderTarget& rt = MainRT_[CurrentMainRT_];

		Effect_->SetTechnique("TransformedPrim");

		//�n�܂�
		Effect_->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		Effect_->BeginPass(0);
		
		//�I�t�Z�b�g�쐬
		float offset[] = 
		{
			0.5f / Engine().GetFrameW(),
			0.5f / Engine().GetFrameH()
		};

		//�e�N�X�`���̐ݒ�
		Effect_->SetTexture("g_Texture", rt.GetTextureDX());
		//�I�t�Z�b�g�̐ݒ�
		Effect_->SetValue("g_Offset", offset, sizeof(offset));

		Effect_->CommitChanges();

		Device_->SetStreamSource(0, Primitive_.GetVertexBuffer()->GetBody(), 0, Primitive_.GetVertexBuffer()->GetStride());
		Device_->SetIndices(Primitive_.GetIndexBuffer()->GetBody());
		Device_->SetVertexDeclaration(Primitive_.GetVertexDecl());
		Device_->DrawIndexedPrimitive(Primitive_.GetD3DPrimitiveType(), 0, 0, Primitive_.GetNumVertex(), 0, Primitive_.GetNumPolygon());

		//�I��
		Effect_->EndPass();
		Effect_->End();
	}

}// namespace nkEngine