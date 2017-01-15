#include"WinMain.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg; 
	
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);

	Initialize();

	// ���b�Z�[�W ���[�v
	do{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			Update();
			Draw();
		}
	} while (msg.message != WM_QUIT);

	graphicsDevice().FreeDX();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	
	switch (mes)
	{
	case WM_KEYDOWN: // �L�[���������Ƃ�
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, mes, wParam, lParam);
	}
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		(TCHAR*)gName,
		NULL
	};
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	hWnd = CreateWindow(
		gName,
		gName,
		WS_VISIBLE | WS_POPUP,
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Initialize()
{
	graphicsDevice().InitD3d(hWnd);
	//SceneManager��initialize
	SINSTANCE(CSceneManager)->InitializeScene();
}

void Update()
{
	//SceneManager��update
	SINSTANCE(CSceneManager)->UpdateScene();

}

void Draw()
{
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		//SceneManager��Draw
		SINSTANCE(CSceneManager)->DrawScene();

		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}