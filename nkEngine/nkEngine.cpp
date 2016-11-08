#include"nkEngine/nkstdafx.h"
#include"nkEngine/nkEngine.h"


namespace nkEngine
{
	bool CEngine::Init(const SInitParam& initParam)
	{
		if(!InitWindow(initParam)){
			return false;
		}
		if(!InitDirectX(initParam)){
			return false;
		}

		m_Physics.Init();

		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		ScreenRender().Init(initParam);
		
		Input.Init(m_hWnd);

		return true;
	}
	
	void CEngine::Final()
	{
		Input.Release();
		SAFE_RELEASE(m_pD3DDevice);
		SAFE_RELEASE(m_pD3D);
	}

	void CEngine::RunGameLoop()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				Time().Update();
				Input.Update();
				XInput().Update();
				m_Physics.Update();
				ScreenRender().Update();
				ScreenRender().Render();
			}
		}
	}

	bool CEngine::InitWindow(const SInitParam& initParam)
	{
		NK_ASSERT(initParam.screenH != 0, "screenHeight is zero");
		NK_ASSERT(initParam.screenW != 0, "screenWigth is zero");

		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_NOCLOSE,
			MsgProc,
			0L, 0L,
			GetModuleHandle(nullptr),
			nullptr, 
			LoadCursor(NULL, IDC_ARROW),
			nullptr, nullptr,
			TEXT("nkmtGames"), nullptr
		};
		RegisterClassEx(&wc);

		RECT rd;
		HWND hDeskWnd = GetDesktopWindow();
		GetWindowRect(hDeskWnd, &rd);
		
		m_hWnd = CreateWindow(
			TEXT("nkmtGames"),
			(LPCSTR)initParam.GameName,
			WS_SYSMENU | WS_MINIMIZEBOX,
			(rd.right - initParam.screenW) / 2,
			(rd.bottom - initParam.screenH) / 2,
			initParam.screenW,
			initParam.screenH,
			nullptr, nullptr,
			wc.hInstance,
			nullptr);

		RECT rw;
		GetWindowRect(m_hWnd, &rw);
		GetClientRect(m_hWnd, &m_cRect);

		int new_width = (rw.right - rw.left) - (m_cRect.right - m_cRect.left) + initParam.screenW;
		int new_height = (rw.bottom - rw.top) - (m_cRect.bottom - m_cRect.top) + initParam.screenH;

		//スクリーン座標中央にウィンドウを初期配置
		SetWindowPos(m_hWnd, NULL, (rd.right - new_width) / 2, (rd.bottom - new_height) / 2, new_width, new_height, SWP_SHOWWINDOW);
		
		//スクリーン座標（0,0）にウィンドウを初期配置
		//SetWindowPos(m_hWnd, NULL, 0,0, new_width, new_height, SWP_SHOWWINDOW);

		return m_hWnd != nullptr;
	}

	bool CEngine::InitDirectX(const SInitParam& initParam)
	{
		if (nullptr == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
			//D3Dオブジェクトを作成できなかった。
			return false;
		}
		//使用できるマルチサンプリングの品質を調べる。
		DWORD quality;
		HRESULT hr = m_pD3D->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, FALSE,
			D3DMULTISAMPLE_4_SAMPLES, &quality
		);

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //D3DFMT_D24X8にするとちらつきが消える
		d3dpp.BackBufferWidth = initParam.frameBufferW;
		d3dpp.BackBufferHeight = initParam.frameBufferH;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
		d3dpp.MultiSampleQuality = quality - 1;
		m_frameBufferW = initParam.frameBufferW;
		m_frameBufferH = initParam.frameBufferH;

		// Create the D3DDevice
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			return false;
		}
		
		return true;
	}

	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
#ifdef _DEBUG
		case WM_KEYDOWN: // キーを押したとき
			switch (wParam) {
				//エスケープキー
			case VK_ESCAPE:
				instance().Final();
				PostQuitMessage(0);
				return 0;
			}
			break;
#endif
		case WM_DESTROY:
			instance().Final();
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return 0L;
	}
}//namesoace nkEngine