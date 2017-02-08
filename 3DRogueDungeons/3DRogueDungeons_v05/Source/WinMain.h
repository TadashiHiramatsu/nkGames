/***********************************************************************/
/*! @file  WinMain.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"AppCommon.h"
#include"GraphicsDevice.h"
#include"SceneManager.h"

TCHAR gName[100] = _T("3DRogueDungeons");

HINSTANCE hInst;
HWND hWnd;
CGraphicsDevice g_graphicsDevice;
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void Initialize();
void Update();
void Draw();