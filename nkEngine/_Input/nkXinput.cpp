#include"nkEngine/nkstdafx.h"
#include"nkXinput.h"

namespace nkEngine
{
	/*!
	*@brief	仮想ボタンとXBoxコントローラのボタンとの関連付けを表す構造体。
	*/
	struct VirtualPadToXPad {
		EButton vButton;		//!<仮想ボタン。
		DWORD	 xButton;		//!<XBoxコントローラのボタン。
	};

	const VirtualPadToXPad vPadToXPadTable[enButtonNum] = {
		{ enButtonUp		, XINPUT_GAMEPAD_DPAD_UP },
		{ enButtonDown		, XINPUT_GAMEPAD_DPAD_DOWN },
		{ enButtonLeft		, XINPUT_GAMEPAD_DPAD_LEFT },
		{ enButtonRight		, XINPUT_GAMEPAD_DPAD_RIGHT },
		{ enButtonA			, XINPUT_GAMEPAD_A },
		{ enButtonB			, XINPUT_GAMEPAD_B },
		{ enButtonY			, XINPUT_GAMEPAD_Y },
		{ enButtonX			, XINPUT_GAMEPAD_X },
		{ enButtonSelect	, XINPUT_GAMEPAD_BACK },
		{ enButtonStart		, XINPUT_GAMEPAD_START },
		{ enButtonRB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
		{ enButtonRB2		, 0 },
		{ enButtonRB3		, XINPUT_GAMEPAD_RIGHT_THUMB },
		{ enButtonLB1		, XINPUT_GAMEPAD_LEFT_SHOULDER },
		{ enButtonLB2		, 0 },
		{ enButtonLB3		, XINPUT_GAMEPAD_LEFT_THUMB },
	};
	/*!
	*@brief	仮想ボタンとキーボードとの関連付けを表す構造体。
	*/
	struct VirtualPadToKeyboard {
		EButton vButton;		//!<仮想ボタン
		DWORD keyCoord;			//!<キーボードのキーコード。
	};
	const VirtualPadToKeyboard vPadToKeyboardTable[enButtonNum] = {
		{ enButtonUp		, '8' },
		{ enButtonDown		, '2' },
		{ enButtonLeft		, '4' },
		{ enButtonRight		, '6' },
		{ enButtonA			, 'J' },
		{ enButtonB			, 'K' },
		{ enButtonY			, 'I' },
		{ enButtonX			, 'O' },
		{ enButtonSelect	, VK_SPACE },
		{ enButtonStart		, VK_RETURN },
		{ enButtonRB1		, '7' },
		{ enButtonRB2		, '8' },
		{ enButtonRB3		, '9' },
		{ enButtonLB1		, 'B' },
		{ enButtonLB2		, 'N' },
		{ enButtonLB3		, 'M' },
	};

	CXinput::CXinput():
		m_padNo(0)
	{
		memset(&m_Controllers, 0, sizeof(m_Controllers));
		memset(m_trigger, 0, sizeof(m_trigger));
		memset(m_press, 0, sizeof(m_press));
		m_LeftStickX = 0.0f;
		m_LeftStickY = 0.0f;
		m_RightStickX = 0.0f;
		m_RightStickY = 0.0f;
		m_LeftTrigger = 0;
		m_RightTrigger = 0;
	}

	CXinput::~CXinput()
	{
		
	}

	void CXinput::Update()
	{
		DWORD result = XInputGetState(m_padNo, &m_Controllers.state);
		if (result == ERROR_SUCCESS) {
			//接続されている。
			m_Controllers.bConnected = true;
			for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable) {
				if (m_Controllers.state.Gamepad.wButtons & vPadToXPad.xButton) {
					m_trigger[vPadToXPad.vButton] = 1 ^ m_press[vPadToXPad.vButton];
					m_press[vPadToXPad.vButton] = 1;
				}
				else {
					m_trigger[vPadToXPad.vButton] = 0;
					m_press[vPadToXPad.vButton] = 0;
				}
			}
			if ((m_Controllers.state.Gamepad.sThumbLX < INPUT_DEADZONE &&
				m_Controllers.state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(m_Controllers.state.Gamepad.sThumbLY < INPUT_DEADZONE &&
					m_Controllers.state.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				m_Controllers.state.Gamepad.sThumbLX = 0;
				m_Controllers.state.Gamepad.sThumbLY = 0;
				m_LeftStickX = 0.0f;
				m_LeftStickY = 0.0f;
			}
			else {
				//左スティックの入力量。正規化
				if (m_Controllers.state.Gamepad.sThumbLX > 0) {
					m_LeftStickX = s_cast<float>(m_Controllers.state.Gamepad.sThumbLX) / SHRT_MAX;
				}
				else {
					m_LeftStickX = s_cast<float>(m_Controllers.state.Gamepad.sThumbLX) / -SHRT_MIN;
				}
				if (m_Controllers.state.Gamepad.sThumbLY > 0) {
					m_LeftStickY = s_cast<float>(m_Controllers.state.Gamepad.sThumbLY) / SHRT_MAX;
				}
				else {
					m_LeftStickY = s_cast<float>(m_Controllers.state.Gamepad.sThumbLY) / -SHRT_MIN;
				}
			}

			if ((m_Controllers.state.Gamepad.sThumbRX < INPUT_DEADZONE &&
				m_Controllers.state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(m_Controllers.state.Gamepad.sThumbRY < INPUT_DEADZONE &&
					m_Controllers.state.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				m_Controllers.state.Gamepad.sThumbRX = 0;
				m_Controllers.state.Gamepad.sThumbRY = 0;
				m_RightStickX = 0.0f;
				m_RightStickY = 0.0f;
			}
			else {
				//右スティックの入力量。
				if (m_Controllers.state.Gamepad.sThumbRX > 0) {
					m_RightStickX = s_cast<float>(m_Controllers.state.Gamepad.sThumbRX) / SHRT_MAX;
				}
				else {
					m_RightStickX = s_cast<float>(m_Controllers.state.Gamepad.sThumbRX) / -SHRT_MIN;
				}
				if (m_Controllers.state.Gamepad.sThumbRY > 0) {
					m_RightStickY = s_cast<float>(m_Controllers.state.Gamepad.sThumbRY) / SHRT_MAX;
				}
				else {
					m_RightStickY = s_cast<float>(m_Controllers.state.Gamepad.sThumbRY) / -SHRT_MIN;
				}
			}
			m_LeftTrigger = m_Controllers.state.Gamepad.bLeftTrigger;
			m_RightTrigger = m_Controllers.state.Gamepad.bRightTrigger;
		}
		else {
			//接続されていない場合はキーボードの入力でエミュレートする。
			if (m_Controllers.bConnected) {
				//未接続になった。
				memset(&m_Controllers, 0, sizeof(m_Controllers));
				memset(m_trigger, 0, sizeof(m_trigger));
				memset(m_press, 0, sizeof(m_press));
			}

			m_LeftStickX = 0.0f;
			m_LeftStickY = 0.0f;
			m_RightStickX = 0.0f;
			m_RightStickY = 0.0f;
			m_LeftTrigger = 0;
			m_RightTrigger = 0;

			if (GetAsyncKeyState(VK_LEFT)) {
				m_RightStickX += -1.0f;
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				m_RightStickX += 1.0f;
			}
			if (GetAsyncKeyState(VK_UP)) {
				m_RightStickY += 1.0f;
			}
			if (GetAsyncKeyState(VK_DOWN)) {
				m_RightStickY += -1.0f;
			}

			if (GetAsyncKeyState('A')) {
				m_LeftStickX += -1.0f;
			}
			if (GetAsyncKeyState('D')) {
				m_LeftStickX += 1.0f;
			}
			if (GetAsyncKeyState('W')) {
				m_LeftStickY += 1.0f;
			}
			if (GetAsyncKeyState('S')) {
				m_LeftStickY += -1.0f;
			}
		
			if (GetAsyncKeyState('1')) {
				m_LeftTrigger = 255;
			}
			if (GetAsyncKeyState('3')) {
				m_RightTrigger = 255;
			}

			for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable) {
				if (GetAsyncKeyState(vPadToKeyboard.keyCoord)) {
					m_trigger[vPadToKeyboard.vButton] = 1 ^ m_press[vPadToKeyboard.vButton];
					m_press[vPadToKeyboard.vButton] = 1;
				}
				else {
					m_trigger[vPadToKeyboard.vButton] = 0;
					m_press[vPadToKeyboard.vButton] = 0;
				}
			}
		}
	}
}