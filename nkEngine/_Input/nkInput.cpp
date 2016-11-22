#include"nkEngine/nkstdafx.h"
#include"nkInput.h"

namespace nkEngine
{

	HRESULT CInput::Init(HWND hWnd)
	{
		HRESULT hr;

		if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&m_DInput, NULL)))
		{
			return hr;
		}

		InitMouse(hWnd);
		InitKeyboard(hWnd);

		return S_OK;
	}
	void CInput::InitMouse(HWND hWnd)
	{
		DIOBJECTDATAFORMAT ObjectFormats[] =
		{
			{ &GUID_XAxis, FIELD_OFFSET(MouseState, PosX),    // X axis
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_YAxis, FIELD_OFFSET(MouseState, PosY),    // Y axis
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseState, Button[0]),        // Button 0
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseState, Button[1]),        // Button 1 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseState, Button[2]),        // Button 2 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 }
		};

		DIDATAFORMAT dfMouse =
		{
			sizeof(DIDATAFORMAT),
			sizeof(DIOBJECTDATAFORMAT),
			DIDF_ABSAXIS,
			sizeof(MouseState),
			sizeof(ObjectFormats) / sizeof(DIOBJECTDATAFORMAT),
			ObjectFormats
		};

		m_DInput->CreateDevice(GUID_SysMouse, &m_DInputMouse, NULL);

		m_DInputMouse->SetDataFormat(&dfMouse);

		m_DInputMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
		m_DInputMouse->Acquire();

	}

	void CInput::InitKeyboard(HWND hWnd)
	{
		m_DInput->CreateDevice(GUID_SysKeyboard,&m_DInputKeyboard,NULL);

		m_DInputKeyboard->SetDataFormat(&c_dfDIKeyboard);

		m_DInputKeyboard->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void CInput::Update()
	{
		HRESULT hr;

		if (m_isMouse)
		{
			GetCursorPos(&MousePos);
			ScreenToClient(Engine().GetHWND(), &MousePos);
			MousePos.y -= Engine().GetScreenH();
			MousePos.y *= -1;

			m_MouseState0 = m_MouseState;
			hr = m_DInputMouse->GetDeviceState(sizeof(MouseState), &m_MouseState);
			if (FAILED(hr))
			{
				m_DInputMouse->Acquire();
				m_DInputMouse->GetDeviceState(sizeof(MouseState), &m_MouseState);
			}
		}

		if (m_isKeyboard)
		{
			hr = m_DInputKeyboard->GetDeviceState(sizeof(m_Keyboard), &m_Keyboard);
			if (FAILED(hr))
			{
				m_DInputKeyboard->Acquire();
				m_DInputKeyboard->GetDeviceState(sizeof(m_Keyboard), &m_Keyboard);
			}
		}
	}

	void CInput::Release()
	{
		if (m_DInputMouse)
		{
			m_DInputMouse->Unacquire();
		}
		if (m_DInputKeyboard)
		{
			m_DInputKeyboard->Unacquire();
		}

		SAFE_RELEASE(m_DInputMouse);
		SAFE_RELEASE(m_DInputKeyboard);
		SAFE_RELEASE(m_DInput);
	}

}