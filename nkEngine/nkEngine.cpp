/**
 * @file	nkEngine.cpp
 *
 * �G���W���N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkEngine/nkEngine.h"

namespace nkEngine
{

	/**
	 * �G���W���̏�����.
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
		//�E�B���h�E�̏�����
		if(!InitWindow(initParam)){
			return false;
		}

		//DirectX�̏�����
		if(!InitDirectX(initParam)){
			return false;
		}

		//�������[���h�̏�����
		Physics_.Init();

		ShowWindow(Hwnd_, SW_SHOWDEFAULT);
		UpdateWindow(Hwnd_);

		//�X�N���[�������_�[�̏�����
		ScreenRender().Start();

		//�Q�[���I�u�W�F�N�g�̏�����
		GameObjectManager().StartGOM(10);
		
		//�C���v�b�g�̏�����
		Input().Init(Hwnd_);

		//�T�E���h�G���W���̏�����.
		SoundEngine_.Init();

		Random::Start();

		return true;
	}

	/**
	 * �I������.
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
	 * �Q�[�����[�v.
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
				//�������[���h�̍X�V
				Physics_.Update();
				//�T�E���h�G���W���̍X�V
				SoundEngine_.Update();

				//�X�N���[�������_�[�̍X�V
				ScreenRender().Loop();
			}
		}
	}

	/**
	 * �E�B���h�E�̏�����.
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
		
		//�E�B���h�E�쐬
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

		//�E�B���h�E�̏����ʒu�v�Z
		int new_width = (rw.right - rw.left) - (ClientRect_.right - ClientRect_.left) + ScreenBufferW_;
		int new_height = (rw.bottom - rw.top) - (ClientRect_.bottom - ClientRect_.top) + ScreenBufferH_;

		if (initParam.isCenter_)
		{
			//�X�N���[�����W�����ɃE�B���h�E�������z�u
			SetWindowPos(Hwnd_, NULL, (rd.right - new_width) / 2, (rd.bottom - new_height) / 2, new_width, new_height, SWP_SHOWWINDOW);
		}
		else
		{
			//�X�N���[�����W�i0,0�j�ɃE�B���h�E�������z�u
			SetWindowPos(Hwnd_, NULL, (rd.right - new_width) / 2,0, new_width, new_height, SWP_SHOWWINDOW);
		}

		return Hwnd_ != nullptr;
	}

	/**
	 * DirectX�̏�����.
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
		//D3D�I�u�W�F�N�g�쐬
		D3DObject_ = Direct3DCreate9(D3D_SDK_VERSION);

		if (D3DObject_ == nullptr)
		{
			//D3D�I�u�W�F�N�g���쐬�ł��Ȃ������B
			return false;
		}

		//�g�p�ł���}���`�T���v�����O�̕i���𒲂ׂ�B
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
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //D3DFMT_D24X8�ɂ���Ƃ������������
		d3dpp.BackBufferWidth = FrameBufferW_;
		d3dpp.BackBufferHeight = FrameBufferH_;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
		d3dpp.MultiSampleQuality = quality - 1;
		
		// D3DDevice�쐬
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
		case WM_KEYDOWN: // �L�[���������Ƃ�
			switch (wParam) {
				//�G�X�P�[�v�L�[
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