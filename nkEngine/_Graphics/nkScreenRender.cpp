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

		//初期化されていないオブジェクトを初期化
		GameObjectManager().Start();

		//プリレンダリング前の更新
		GameObjectManager().PreUpdate();

		//プリレンダリング
		Shadow().Update(); 

		//更新
		GameObjectManager().Update();

		//Updateの後の更新
		GameObjectManager().PostUpdate();


		IDirect3DDevice9* Device = Engine().GetDevice();

		Device->BeginScene();

		Device->SetRenderTarget(0, m_rtMain.GetSurface());
		Device->SetDepthStencilSurface(m_rtMain.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		//プリレンダーの描画
		Shadow().Render();

		//Renderの前の描画
		GameObjectManager().PreRender();

		//描画
		GameObjectManager().Render();

		//ポストエフェクト
		//m_Bloom.Render();

		Device->SetRenderTarget(0, m_rtBackBuffer.GetSurface());
		Device->SetDepthStencilSurface(m_rtBackBuffer.GetDepthSurface());
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		m_AntiAliasing.Render();

		//ポストエフェクトの後の描画
		GameObjectManager().PostRender();

		Device->EndScene();
		Device->Present(NULL, NULL, NULL, NULL);

		//削除登録されたGameObjectを削除
		GameObjectManager().Delete();
	}
}