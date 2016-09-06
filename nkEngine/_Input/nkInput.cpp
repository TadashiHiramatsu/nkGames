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
		//InitJoystick(hWnd);

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

	//void CInput::InitJoystick(HWND hWnd)
	//{
	//	DIOBJECTDATAFORMAT ObjectFormats[] =
	//	{
	//		{ &GUID_XAxis, FIELD_OFFSET(JoystickState, LeftStick[0]),    
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_YAxis, FIELD_OFFSET(JoystickState, LeftStick[1]),  
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_XAxis, FIELD_OFFSET(JoystickState, RightStick[0]),
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_YAxis, FIELD_OFFSET(JoystickState, RightStick[1]),
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[0]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[1]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[2]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[3]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[4]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[5]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[6]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[7]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[8]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[9]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[10]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[11]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[12]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[13]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[14]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[15]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[16]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[17]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[18]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Button, FIELD_OFFSET(JoystickState, Button[19]),
	//		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Slider, FIELD_OFFSET(JoystickState, Shoulder[0]),
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
	//		{ &GUID_Slider, FIELD_OFFSET(JoystickState, Shoulder[1]),
	//		DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 }
	//	};

	//	DIDATAFORMAT dfJoystick =
	//	{
	//		sizeof(DIDATAFORMAT),
	//		sizeof(DIOBJECTDATAFORMAT),
	//		DIDF_ABSAXIS,
	//		sizeof(MouseState),
	//		sizeof(ObjectFormats) / sizeof(DIOBJECTDATAFORMAT),
	//		ObjectFormats
	//	};

	//	m_DInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);

	//	if (m_DInputJoystick != nullptr)
	//	{
	//		m_DInputJoystick->SetDataFormat(&dfJoystick);

	//		m_DInputJoystick->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	//		m_DInputJoystick->EnumObjects(EnumAxesCallback, NULL, DIDFT_AXIS);

	//		m_DInputJoystick->Acquire();
	//	}
	//	else
	//	{
	//		m_isJoystick = false;
	//	}
	//}

	//BOOL CInput::EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
	//{

	//	HRESULT hr;

	//	hr = GetInstance().m_DInput->CreateDevice(lpddi->guidInstance, &GetInstance().m_DInputJoystick, NULL);
	//	if (FAILED(hr)) return DIENUM_CONTINUE;

	//	// ジョイスティックの能力を調べる
	//	GetInstance().m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
	//	hr = GetInstance().m_DInputJoystick->GetCapabilities(&GetInstance().m_diDevCaps);
	//	if (FAILED(hr))
	//	{
	//		return DIENUM_CONTINUE;
	//	}
	//	return DIENUM_STOP;

	//}

	//BOOL CALLBACK CInput::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
	//{
	//	HRESULT hr;

	//	// 軸の値の範囲を設定（-1000～1000）
	//	DIPROPRANGE diprg;
	//	ZeroMemory(&diprg, sizeof(diprg));
	//	diprg.diph.dwSize = sizeof(diprg);
	//	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	//	diprg.diph.dwObj = lpddoi->dwType;
	//	diprg.diph.dwHow = DIPH_BYID;
	//	diprg.lMin = -1000;
	//	diprg.lMax = +1000;
	//	hr = GetInstance().m_DInputJoystick->SetProperty(DIPROP_RANGE, &diprg.diph);
	//	if (FAILED(hr))     return DIENUM_STOP;
	//	return DIENUM_CONTINUE;
	//}

	void CInput::Update()
	{
		HRESULT hr;

		if (m_isMouse)
		{
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

		/*if (m_isJoystick)
		{
			m_JoystickState;
			hr = m_DInputJoystick->GetDeviceState(sizeof(m_JoystickState), &m_JoystickState);
			if (FAILED(hr))
			{
				m_DInputJoystick->Acquire();
				m_DInputJoystick->GetDeviceState(sizeof(m_JoystickState), &m_JoystickState);
			}
		}*/
		
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