/***********************************************************************/
/*! @file  WinMain.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"WinMain.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hInstance 
 *  @param[in,out] hPrevInstance 
 *  @param[in,out] lpCmdLine 
 *  @param[in,out] nCmdShow 
 *  @retval int APIENTRY 
 */
/***********************************************************************/
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg; 
	
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);

	Initialize();

	// メッセージ ループ
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

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hWnd 
 *  @param[in,out] mes 
 *  @param[in,out] wParam 
 *  @param[in,out] lParam 
 *  @retval LRESULT CALLBACK 
 */
/***********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	
	switch (mes)
	{
	case WM_KEYDOWN: // キーを押したとき
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

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hInstance 
 *  @retval ATOM 
 */
/***********************************************************************/
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

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] hInstance 
 *  @param[in,out] nCmdShow 
 *  @retval BOOL 
 */
/***********************************************************************/
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

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void Initialize()
{
	graphicsDevice().InitD3d(hWnd);
	//SceneManagerのinitialize
	SINSTANCE(CSceneManager)->InitializeScene();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void Update()
{
	//SceneManagerのupdate
	SINSTANCE(CSceneManager)->UpdateScene();

}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void Draw()
{
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		//SceneManagerのDraw
		SINSTANCE(CSceneManager)->DrawScene();

		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}
