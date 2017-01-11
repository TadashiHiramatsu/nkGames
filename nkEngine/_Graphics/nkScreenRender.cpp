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
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CScreenRender::CScreenRender()
	{
	}

	/**
	 * �f�X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CScreenRender::~CScreenRender()
	{
	}

	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param initParam The init parameter.
	 */
	void CScreenRender::Start(const InitParamS& initParam)
	{
		//���C�������_�[�^�[�Q�b�g�̍쐬
		MainRT_.Create(initParam.FrameBufferW_, initParam.FrameBufferH_, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		//�A���`�G�C���A�V���O�̏�����
		AntiAliasing_.Init();

		//�u���[���̏�����
		Bloom_.Create(false);

		//�o�b�N�o�b�t�@�����_�[�^�[�Q�b�g�̍쐬
		LPDIRECT3DSURFACE9 rt, depth;
		Engine().GetDevice()->GetRenderTarget(0, &rt);
		Engine().GetDevice()->GetDepthStencilSurface(&depth);
		BackBufferRT_.SetSurface(rt);
		BackBufferRT_.SetDepthSurface(depth);

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

		//�f�o�C�X�̎擾
		IDirect3DDevice9* Device = Engine().GetDevice();

		//�V�[���̊J�n
		Device->BeginScene();

		//�����_�[�^�[�Q�b�g�����C�������_�[�ɐݒ�
		Device->SetRenderTarget(0, MainRT_.GetSurface());
		Device->SetDepthStencilSurface(MainRT_.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//�v�������_�[�̕`��
		Shadow().Render();

		//Render�̑O�̕`��
		GameObjectManager().PreRender();

		//�`��
		GameObjectManager().Render();

		//�|�X�g�G�t�F�N�g
		//Bloom_.Render();

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
		Device->SetRenderTarget(0, BackBufferRT_.GetSurface());
		Device->SetDepthStencilSurface(BackBufferRT_.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//�A���`�G�C���A�V���O�̕`��
		AntiAliasing_.Render();

		//�|�X�g�G�t�F�N�g�̌�̕`��
		GameObjectManager().PostRender();

		//�V�[���̏I��
		Device->EndScene();
		Device->Present(NULL, NULL, NULL, NULL);

		//�폜�o�^���ꂽGameObject���폜
		GameObjectManager().Delete();
	}

}// namespace nkEngine