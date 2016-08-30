#include"nkEngine/nkstdafx.h"
#include"nkOffScreenRender.h"

namespace nkEngine
{
	void COffScreenRender::Init(const SInitParam & initParam)
	{
		m_RenderTarget.Create(initParam.frameBufferW, initParam.frameBufferH, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
		m_viewport = { 0,0,(DWORD)initParam.frameBufferW,(DWORD)initParam.frameBufferH,0.0f,1.0f };

		full.Load();
		full.Init();
	}
	void COffScreenRender::Update()
	{
		full.Update(D3DXVECTOR3(Engine().GetFrameW() / 2, Engine().GetFrameH() / 2, 0), D3DXVECTOR3(Engine().GetFrameW(), Engine().GetFrameH(), 0));
		SceneManager().UpdateScene();
		Shadow().Update();
	}
	void COffScreenRender::Render()
	{
		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->BeginScene();

		D3DVIEWPORT9       viewport;
		LPDIRECT3DSURFACE9 BackBuffer;
		LPDIRECT3DSURFACE9 BackDepthBuffer;

		Device->GetViewport(&viewport);
		Device->GetRenderTarget(0, &BackBuffer);
		Device->GetDepthStencilSurface(&BackDepthBuffer);

		Device->SetRenderTarget(0, m_RenderTarget.GetSurface());
		Device->SetDepthStencilSurface(m_RenderTarget.GetDepthSurface());
		Device->SetViewport(&m_viewport);
		Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		
		//Œ»Ý‚ÌƒV[ƒ“‚Ì•`‰æ
		Shadow().Render();
		SceneManager().RenderScene();

		Device->SetRenderTarget(0, BackBuffer);
		Device->SetDepthStencilSurface(BackDepthBuffer);
		Device->SetViewport(&viewport);
		Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//‚±‚±‚Å2DŽg‚Á‚Ä•`‰æ‚·‚ê‚Î‚¨‚‹
		full.SetTexture(m_RenderTarget.GetTexture()->GetTextureDX());
		full.Render();


		Device->EndScene();
		Device->Present(NULL, NULL, NULL, NULL);
	
	}
}