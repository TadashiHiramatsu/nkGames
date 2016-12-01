#include"nkEngine/nkstdafx.h"
#include"nkScreenRender.h"

namespace nkEngine
{
	CScreenRender::CScreenRender()
	{
	}

	CScreenRender::~CScreenRender()
	{
	}

	void CScreenRender::Start(const SInitParam & initParam)
	{
		m_rtMain.Create(initParam.frameBufferW, initParam.frameBufferH, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		m_AntiAliasing.Init();
		m_Bloom.Create(false);

		LPDIRECT3DSURFACE9 rt, depth;
		Engine().GetDevice()->GetRenderTarget(0, &rt);
		Engine().GetDevice()->GetDepthStencilSurface(&depth);
		m_rtBackBuffer.SetSurface(rt);
		m_rtBackBuffer.SetDepthSurface(depth);
	}

	void CScreenRender::Loop()
	{
		Time().Update();
		Input.Update();
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


		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->BeginScene();

		Device->SetRenderTarget(0, m_rtMain.GetSurface());
		Device->SetDepthStencilSurface(m_rtMain.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//�v�������_�[�̕`��
		Shadow().Render();

		//Render�̑O�̕`��
		GameObjectManager().PreRender();

		//�`��
		GameObjectManager().Render();

		//�|�X�g�G�t�F�N�g
		//m_Bloom.Render();

		Device->SetRenderTarget(0, m_rtBackBuffer.GetSurface());
		Device->SetDepthStencilSurface(m_rtBackBuffer.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		m_AntiAliasing.Render();

		//�|�X�g�G�t�F�N�g�̌�̕`��
		GameObjectManager().PostRender();

		Device->EndScene();
		Device->Present(NULL, NULL, NULL, NULL);

		//�폜�o�^���ꂽGameObject���폜
		GameObjectManager().Delete();
	}
}