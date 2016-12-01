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

	enum MouseButton
	{
		MouseLeft,
		MouseRight,
		MouseWheel,
	};

	enum KeyCode
	{
		Escape = DIK_ESCAPE,
		Alpha1 = DIK_1,			// �L�[�{�[�h��1
		Alpha2 = DIK_2,			// �L�[�{�[�h��2
		Alpha3 = DIK_3,			// �L�[�{�[�h��3
		Alpha4 = DIK_4,			// �L�[�{�[�h��4
		Alpha5 = DIK_5,			// �L�[�{�[�h��5
		Alpha6 = DIK_6,			// �L�[�{�[�h��6
		Alpha7 = DIK_7,			// �L�[�{�[�h��7
		Alpha8 = DIK_8,			// �L�[�{�[�h��8
		Alpha9 = DIK_9,			// �L�[�{�[�h��9
		Alpha0 = DIK_0,			// �L�[�{�[�h��0
		Minus = DIK_MINUS,		// -
//#define DIK_EQUALS          
		Backspace = DIK_BACK,
		Tab = DIK_TAB,
		Q = DIK_Q,
		W = DIK_W,
		E = DIK_E,
		R = DIK_R,
		T = DIK_T,
		Y = DIK_Y,
		U = DIK_U,
		I = DIK_I,
		O = DIK_O,
		P = DIK_P,
		Bracket_L = DIK_LBRACKET, // [
		Bracket_R = DIK_RBRACKET, // ]
		Enter = DIK_RETURN,
		Control_L = DIK_LCONTROL,
		A = DIK_A,
		S = DIK_S,
		D = DIK_D,
		F = DIK_F,
		G = DIK_G,
		H = DIK_H,
		J = DIK_J,
		K = DIK_K,
		L = DIK_L,
		Semicolon = DIK_SEMICOLON, // ;
		Apostrophe = DIK_APOSTROPHE, //@
//#define DIK_GRAVE               /* accent grave */
		Shift_L = DIK_LSHIFT,
		BackSlash = DIK_BACKSLASH,	// 
		Z = DIK_Z,               
		X = DIK_X,
		C = DIK_C,
		V = DIK_V,
		B = DIK_B,
		N = DIK_N,
		M = DIK_M,
		Comma = DIK_COMMA, // ,           
		Period = DIK_PERIOD,  // .           
		Slash = DIK_SLASH,   // /   
		Shift_R = DIK_RSHIFT,
//#define DIK_MULTIPLY            /* * on numeric keypad */
		LeftAlt = DIK_LMENU,
		Space = DIK_SPACE,
//#define DIK_CAPITAL
		F1 = DIK_F1,
		F2 = DIK_F2,
		F3 = DIK_F3,
		F4 = DIK_F4,
		F5 = DIK_F5,
		F6 = DIK_F6,
		F7 = DIK_F7,
		F8 = DIK_F8,
		F9 = DIK_F9,
		F10 = DIK_F10,
		NumLock = DIK_NUMLOCK,
//#define DIK_SCROLL              /* Scroll Lock */
		Keypad7 = DIK_NUMPAD7,
		Keypad8 = DIK_NUMPAD8,
		Keypad9 = DIK_NUMPAD9,
		KeypadMinus = DIK_SUBTRACT,
		Keypad4 = DIK_NUMPAD4,
		Keypad5 = DIK_NUMPAD5,
		Keypad6 = DIK_NUMPAD6,
		KeypadPlus = DIK_ADD,
		Keypad1 = DIK_NUMPAD1,
		Keypad2 = DIK_NUMPAD2,
		Keypad3 = DIK_NUMPAD3,
		Keypad0 = DIK_NUMPAD0,
		KeypadPeriod = DIK_DECIMAL, //DEL
//#define DIK_OEM_102             /* <> or \| on RT 102-key keyboard (Non-U.S.) */
		F11 = DIK_F11,
		F12 = DIK_F12,
		F13 = DIK_F13,                /*                     (NEC PC98) */
		F14 = DIK_F14,               /*                     (NEC PC98) */
		F15 = DIK_F15,                 /*                     (NEC PC98) */
//#define DIK_KANA                /* (Japanese keyboard)            */
//#define DIK_ABNT_C1             /* /? on Brazilian keyboard */
//#define DIK_CONVERT             /* (Japanese keyboard)            */
//#define DIK_NOCONVERT           /* (Japanese keyboard)            */
//#define DIK_YEN                 /* (Japanese keyboard)            */
//#define DIK_ABNT_C2             /* Numpad . on Brazilian keyboard */
//#define DIK_NUMPADEQUALS        /* = on numeric keypad (NEC PC98) */
//#define DIK_PREVTRACK           /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
//#define DIK_AT                  /*                     (NEC PC98) */
//#define DIK_COLON               /*                     (NEC PC98) */
//#define DIK_UNDERLINE           /*                     (NEC PC98) */
//#define DIK_KANJI               /* (Japanese keyboard)            */
//#define DIK_STOP                /*                     (NEC PC98) */
//#define DIK_AX                  /*                     (Japan AX) */
//#define DIK_UNLABELED           /*                        (J3100) */
//#define DIK_NEXTTRACK           /* Next Track */
//#define DIK_NUMPADENTER         /* Enter on numeric keypad */
		Control_R = DIK_RCONTROL,
//#define DIK_MUTE                /* Mute */
//#define DIK_CALCULATOR          /* Calculator */
//#define DIK_PLAYPAUSE           /* Play / Pause */
//#define DIK_MEDIASTOP           /* Media Stop */
//#define DIK_VOLUMEDOWN          /* Volume - */
//#define DIK_VOLUMEUP            /* Volume + */
//#define DIK_WEBHOME             /* Web home */
//#define DIK_NUMPADCOMMA         /* , on numeric keypad (NEC PC98) */
//#define DIK_DIVIDE              /* / on numeric keypad */
//#define DIK_SYSRQ           
//#define DIK_RMENU               /* right Alt */
//#define DIK_PAUSE               /* Pause */
//#define DIK_HOME                /* Home on arrow keypad */
		Up = DIK_UP,                  /* UpArrow on arrow keypad */
//#define DIK_PRIOR               /* PgUp on arrow keypad */
		Left = DIK_LEFT,                /* LeftArrow on arrow keypad */
		Right = DIK_RIGHT,               /* RightArrow on arrow keypad */
//#define DIK_END                 /* End on arrow keypad */
		Down = DIK_DOWN,                /* DownArrow on arrow keypad */
//#define DIK_NEXT                /* PgDn on arrow keypad */
//#define DIK_INSERT              /* Insert on arrow keypad */
//#define DIK_DELETE              /* Delete on arrow keypad */
//#define DIK_LWIN                /* Left Windows key */
//#define DIK_RWIN                /* Right Windows key */
//#define DIK_APPS                /* AppMenu key */
//#define DIK_POWER               /* System Power */
//#define DIK_SLEEP               /* System Sleep */
//#define DIK_WAKE                /* System Wake */
//#define DIK_WEBSEARCH           /* Web Search */
//#define DIK_WEBFAVORITES        /* Web Favorites */
//#define DIK_WEBREFRESH          /* Web Refresh */
//#define DIK_WEBSTOP             /* Web Stop */
//#define DIK_WEBFORWARD          /* Web Forward */
//#define DIK_WEBBACK             /* Web Back */
//#define DIK_MYCOMPUTER          /* My Computer */
//#define DIK_MAIL                /* Mail */
//#define DIK_MEDIASELECT         /* Media Select */
	};

	class CInput
	{
	public:
		//������
		HRESULT Init(HWND hWnd);

		//�X�V
		void Update();
			
		//�J��
		void Release();

		//X���̈ړ��ʂ�Ԃ�
		LONG GetMouseX()
		{
			return m_MouseState0.PosX - m_MouseState.PosX;
		}

		//Y���̈ړ��ʂ�Ԃ�
		LONG GetMouseY()
		{
			return m_MouseState0.PosY - m_MouseState.PosY;
		}

		//X���̍��W��Ԃ�
		LONG GetMousePosX()
		{
			return MousePos.x;
		}

		//Y���̍��W��Ԃ�
		LONG GetMousePosY()
		{
			return MousePos.y;
		}

		//�}�E�X�̃{�^����������Ă��邩
		bool GetMoudeButton(int idx)
		{
			return (m_MouseState.Button[idx] & 0x80);
		}
		bool GetMoudeButton(MouseButton idx)
		{
			return (m_MouseState.Button[idx] & 0x80);
		}

		//�}�E�X�̃{�^���������ꂽ
		bool GetMoudeButtonDown(int idx)
		{
			return(!(m_MouseState0.Button[idx] & 0x80) && m_MouseState.Button[idx] & 0x80) ;
		}
		bool GetMoudeButtonDown(MouseButton idx)
		{
			return(!(m_MouseState0.Button[idx] & 0x80) && m_MouseState.Button[idx] & 0x80) ;
		}

		//�}�E�X�̃{�^�����͂Ȃ��ꂽ
		bool GetMoudeButtonUp(int idx)
		{
			return (m_MouseState0.Button[idx] & 0x80 && !(m_MouseState.Button[idx] & 0x80)) ;
		}
		bool GetMoudeButtonUp(MouseButton idx)
		{
			return(m_MouseState0.Button[idx] & 0x80 && !(m_MouseState.Button[idx] & 0x80)) ;
		}

		bool GetKeyButton(KeyCode key)
		{
			return (bool)(m_Keyboard[key] & 0x80);
		}
		bool GetKeyButtonDown(KeyCode key)
		{
			return (bool)(!(m_Keyboard0[key] & 0x80) && m_Keyboard[key] & 0x80);
		}
		bool GetKeyButtonUp(KeyCode key)
		{
			return (bool)(m_Keyboard0[key] & 0x80 && !(m_Keyboard[key] & 0x80));
		}

		inline static CInput& GetInstance()
		{
			static CInput instance;
			return instance;
		}

	private:
		CInput():
			m_isKeyboard(true),
			m_isMouse(true)
		{
		}
		~CInput()
		{

		}

		//�}�E�X������
		void InitMouse(HWND hWnd);

		//�L�[�{�[�h������
		void InitKeyboard(HWND hWnd);

	private:
		MouseState m_MouseState; //���݂̃}�E�X�X�e�[�^�X
		MouseState m_MouseState0; //���O�̃}�E�X�X�e�[�^�X
		POINT MousePos;
		BYTE m_Keyboard[256]; //���݂̃L�[�{�[�h�X�e�[�^�X
		BYTE m_Keyboard0[256]; //���O�̃L�[�{�[�h�X�e�[�^�X
		
		IDirectInputDevice8* m_DInputMouse = nullptr; //�}�E�X�f�o�C�X
		IDirectInputDevice8* m_DInputKeyboard = nullptr; //�L�[�{�[�h�f�o�C�X
		IDirectInput8* m_DInput = nullptr; //�Ȃ��ɂ��ꂥ

		bool m_isKeyboard; //�L�[�{�[�h���g�p����
		bool m_isMouse; //�}�E�X���g�p����
	};

	inline static CInput& GetInput()
	{
		return CInput::GetInstance();
	}

#define Input GetInput()
}

