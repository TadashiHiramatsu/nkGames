#pragma once

namespace nkEngine
{
	struct MouseState
	{
		LONG PosX;
		LONG PosY;
		BYTE Button[3];
		BYTE Padding;
		MouseState()
		{
			memset(this, 0, sizeof(MouseState));
		}
	};

	//struct JoystickState
	//{
	//	LONG LeftStick[2]; //0:縦,1:横
	//	LONG RightStick[2]; //0:縦,1:横
	//	BYTE Button[20]; //まだわからん
	//	LONG Shoulder[2]; //0:左,1:右
	//};

	class CInput
	{
	public:
		//初期化
		HRESULT Init(HWND hWnd);

		//更新
		void Update();
			
		//開放
		void Release();

		//X軸の移動量を返す
		LONG GetMovementX()
		{
			return m_MouseState0.PosX - m_MouseState.PosX;
		}

		//Y軸の移動量を返す
		LONG GetMovementY()
		{
			return m_MouseState0.PosY - m_MouseState.PosY;
		}

		bool GetButton(int idx)
		{
			return (m_MouseState.Button[idx] & 0x80);
		}

		bool GetKeyButton(int idx)
		{
			return (m_Keyboard[idx] & 0x80);
		}

		inline static CInput& GetInstance()
		{
			static CInput instance;
			return instance;
		}

	private:
		CInput():
			m_isKeyboard(true),
			m_isMouse(true),
			m_isJoystick(true)
		{
		}
		~CInput()
		{

		}

		//マウス初期化
		void InitMouse(HWND hWnd);

		//キーボード初期化
		void InitKeyboard(HWND hWnd);

		//ジョイスティック初期化
		//void InitJoystick(HWND hWnd);

		//static BOOL PASCAL EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
		//static BOOL PASCAL EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	private:
		MouseState m_MouseState; //現在のマウスステータス
		MouseState m_MouseState0; //一回前のマウスステータス
		BYTE m_Keyboard[256]; //現在のキーボードステータス
		
		//JoystickState m_JoystickState;

		IDirectInputDevice8* m_DInputMouse = nullptr; //マウスデバイス
		IDirectInputDevice8* m_DInputKeyboard = nullptr; //キーボードデバイス
		//IDirectInputDevice8* m_DInputJoystick = nullptr; //ジョイスティックデバイス
		IDirectInput8* m_DInput = nullptr; //なぁにこれぇ

		//DIDEVCAPS m_diDevCaps; // ジョイスティックの能力

		bool m_isKeyboard; //キーボードを使用する
		bool m_isMouse; //マウスを使用する
		bool m_isJoystick; //ジョイスティックを使用する
	};

	inline static CInput& Input()
	{
		return CInput::GetInstance();
	}
}

