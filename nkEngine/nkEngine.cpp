/**
 * @file	nkEngine.cpp
 *
 * エンジンクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkEngine/nkEngine.h"

namespace nkEngine
{

	/**
	 * エンジンの初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	initParam	The init parameter.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */
	bool CEngine::Init(const InitParamS& initParam)
	{
		//ウィンドウの初期化
		if(!InitWindow(initParam)){
			return false;
		}

		//DirectXの初期化
		if(!InitDirectX(initParam)){
			return false;
		}

		//物理ワールドの初期化
		Physics_.Init();

		ShowWindow(Hwnd_, SW_SHOWDEFAULT);
		UpdateWindow(Hwnd_);

		//スクリーンレンダーの初期化
		ScreenRender().Start();

		//ゲームオブジェクトの初期化
		GameObjectManager().StartGOM(10);
		
		//インプットの初期化
		Input().Init(Hwnd_);

		//サウンドエンジンの初期化.
		SoundEngine_.Init();

		Random::Start();

		return true;
	}

	/**
	 * 終了処理.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	void CEngine::Final()
	{
		Input().Release();
		SAFE_RELEASE(D3DDevice_);
		SAFE_RELEASE(D3DObject_);
	}

	/**
	 * ゲームループ.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
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
				//物理ワールドの更新
				Physics_.Update();
				//サウンドエンジンの更新
				SoundEngine_.Update();

				//スクリーンレンダーの更新
				ScreenRender().Loop();
			}
		}
	}

	/**
	 * ウィンドウの初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	initParam	The init parameter.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */
	bool CEngine::InitWindow(const InitParamS& initParam)
	{
		NK_ASSERT(initParam.ScreenBufferW_ != 0, "screenWigth is zero");
		NK_ASSERT(initParam.ScreenBufferH_ != 0, "screenHeight is zero");

		ScreenBufferW_ = initParam.ScreenBufferW_;
		ScreenBufferH_ = initParam.ScreenBufferH_;
		FrameBufferW_ = initParam.FrameBufferW_;
		FrameBufferH_ = initParam.FrameBufferH_;

		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_NOCLOSE,
			MsgProc,
			0L, 0L,
			GetModuleHandle(nullptr),
			nullptr, 
			LoadCursor(NULL, IDC_ARROW),
			nullptr, 
			nullptr,
			TEXT("nkmtGames"), 
			nullptr
		};
		RegisterClassEx(&wc);

		RECT rd;
		HWND hDeskWnd = GetDesktopWindow();
		GetWindowRect(hDeskWnd, &rd);
		
		//ウィンドウ作成
		Hwnd_ = CreateWindow(
			TEXT("nkmtGames"),
			(LPCSTR)initParam.GameName_,
			WS_SYSMENU | WS_MINIMIZEBOX,
			(rd.right - ScreenBufferW_) / 2,
			(rd.bottom - ScreenBufferH_) / 2,
			ScreenBufferW_,
			ScreenBufferH_,
			nullptr,
			nullptr,
			wc.hInstance,
			nullptr
		);

		RECT rw;
		GetWindowRect(Hwnd_, &rw);
		GetClientRect(Hwnd_, &ClientRect_);

		//ウィンドウの初期位置計算
		int new_width = (rw.right - rw.left) - (ClientRect_.right - ClientRect_.left) + ScreenBufferW_;
		int new_height = (rw.bottom - rw.top) - (ClientRect_.bottom - ClientRect_.top) + ScreenBufferH_;

		if (initParam.isCenter_)
		{
			//スクリーン座標中央にウィンドウを初期配置
			SetWindowPos(Hwnd_, NULL, (rd.right - new_width) / 2, (rd.bottom - new_height) / 2, new_width, new_height, SWP_SHOWWINDOW);
		}
		else
		{
			//スクリーン座標（0,0）にウィンドウを初期配置
			SetWindowPos(Hwnd_, NULL, (rd.right - new_width) / 2,0, new_width, new_height, SWP_SHOWWINDOW);
		}

		return Hwnd_ != nullptr;
	}

	/**
	 * DirectXの初期化.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	initParam	The init parameter.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */
	bool CEngine::InitDirectX(const InitParamS& initParam)
	{
		//D3Dオブジェクト作成
		D3DObject_ = Direct3DCreate9(D3D_SDK_VERSION);

		if (D3DObject_ == nullptr)
		{
			//D3Dオブジェクトを作成できなかった。
			return false;
		}

		//使用できるマルチサンプリングの品質を調べる。
		DWORD quality;
		HRESULT hr = D3DObject_->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			D3DFMT_A8R8G8B8,
			FALSE,
			D3DMULTISAMPLE_4_SAMPLES, 
			&quality
		);

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //D3DFMT_D24X8にするとちらつきが消える
		d3dpp.BackBufferWidth = FrameBufferW_;
		d3dpp.BackBufferHeight = FrameBufferH_;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
		d3dpp.MultiSampleQuality = quality - 1;
		
		// D3DDevice作成
		if (FAILED(D3DObject_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Hwnd_,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &D3DDevice_)))
		{
			return false;
		}
		
		return true;
	}

	/**
	 * Message proc.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param	hWnd  	Handle of the window.
	 * @param	msg   	The message.
	 * @param	wParam	The wParam field of the message.
	 * @param	lParam	The lParam field of the message.
	 *
	 * @return	A CALLBACK.
	 */
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
//#ifdef _DEBUG
		case WM_KEYDOWN: // キーを押したとき
			switch (wParam) {
				//エスケープキー
			case VK_ESCAPE:
				instance().Final();
				PostQuitMessage(0);
				return 0;
			}
			break;
//#endif
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