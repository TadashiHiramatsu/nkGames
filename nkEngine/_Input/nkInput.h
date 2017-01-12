/**
 * @file	_Input\nkInput.h
 *
 * DirectInput�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{
	/**
	 * �}�E�X�X�e�[�g.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/09
	 */
	struct MouseStateS
	{
	public:

		/**
		* Default constructor.
		*
		* @author	HiramatsuTadashi
		* @date	2017/01/09
		*/
		MouseStateS()
		{
			memset(this, 0, sizeof(MouseStateS));
		}

	public:

		/** �}�E�X�̃|�W�V����:X���W. */
		LONG PosX_;
		/** �}�E�X�̃|�W�V����:Y���W. */
		LONG PosY_;
		/**   
		 * �{�^��. 
		 * MouseButtonE�ɏ�����.
		 */
		BYTE Button_[3];
		/** The padding. */
		BYTE Padding_;
		
	};

	/** �}�E�X�{�^���̗񋓒l. */
	enum MouseButtonE
	{
		MouseLeft = 0,	//!< ��.
		MouseRight,		//!< �E.
		MouseWheel,		//!< �z�C�[��.
	};

	enum KeyCodeE
	{
		Escape = DIK_ESCAPE,
		Alpha1 = DIK_1,			//!< �L�[�{�[�h��1.
		Alpha2 = DIK_2,			//!< �L�[�{�[�h��2.
		Alpha3 = DIK_3,			//!< �L�[�{�[�h��3.
		Alpha4 = DIK_4,			//!< �L�[�{�[�h��4.
		Alpha5 = DIK_5,			//!< �L�[�{�[�h��5.
		Alpha6 = DIK_6,			//!< �L�[�{�[�h��6.
		Alpha7 = DIK_7,			//!< �L�[�{�[�h��7.
		Alpha8 = DIK_8,			//!< �L�[�{�[�h��8.
		Alpha9 = DIK_9,			//!< �L�[�{�[�h��9.
		Alpha0 = DIK_0,			//!< �L�[�{�[�h��0.
		Minus = DIK_MINUS,		//!< -.
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
		Bracket_L = DIK_LBRACKET, //!< [.
		Bracket_R = DIK_RBRACKET, //!< ].
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
		Semicolon = DIK_SEMICOLON, //!< ;.
		Apostrophe = DIK_APOSTROPHE, //!< @.
//#define DIK_GRAVE               /* accent grave */
		Shift_L = DIK_LSHIFT,
		BackSlash = DIK_BACKSLASH,	//!< .
		Z = DIK_Z,               
		X = DIK_X,
		C = DIK_C,
		V = DIK_V,
		B = DIK_B,
		N = DIK_N,
		M = DIK_M,
		Comma = DIK_COMMA, //!< ,.        
		Period = DIK_PERIOD,  //!< ..           
		Slash = DIK_SLASH,   //!< /.  
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
//!<#define DIK_SCROLL              /* Scroll Lock */
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
		KeypadPeriod = DIK_DECIMAL, //!< DEL.
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

	/**
	 * DirectInput�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/09
	 */
	class CInput
	{
	private:

		/**
		* Default constructor.
		*
		* @author	HiramatsuTadashi
		* @date	2017/01/09
		*/
		CInput() :
			isKeyboard_(true),
			isMouse_(true)
		{
		}

		/**
		* Destructor.
		*
		* @author	HiramatsuTadashi
		* @date	2017/01/09
		*/
		~CInput()
		{
		}

	public:

		/**
		 * ������.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	hWnd	Handle of the window.
		 *
		 * @return	A hResult.
		 */
		HRESULT Init(HWND hWnd);
		
		/**
		 * �X�V.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 */
		void Update();
		
		/**
		 * �J��.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 */
		void Release();

		/**
		 * X���̈ړ��ʂ�Ԃ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @return	The mouse x coordinate.
		 */
		LONG GetMouseX()
		{
			return MouseStateBef_.PosX_ - MouseState_.PosX_;
		}

		/**
		 * Y���̈ړ��ʂ�Ԃ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @return	The mouse y coordinate.
		 */
		LONG GetMouseY()
		{
			return MouseStateBef_.PosY_ - MouseState_.PosY_;
		}

		/**
		 * X���̍��W��Ԃ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @return	The mouse position x coordinate.
		 */
		LONG GetMousePosX()
		{
			return MousePos_.x;
		}

		/**
		 * Y���̍��W��Ԃ�.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @return	The mouse position y coordinate.
		 */
		LONG GetMousePosY()
		{
			return MousePos_.y;
		}

		/**
		 * �}�E�X�̃{�^����������Ă��邩.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButton(int idx)
		{
			return (MouseState_.Button_[idx] & 0x80);
		}
		/**
		 * �}�E�X�̃{�^����������Ă��邩.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButton(MouseButtonE idx)
		{
			return (MouseState_.Button_[idx] & 0x80);
		}

		/**
		 * �}�E�X�̃{�^���������ꂽ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButtonDown(int idx)
		{
			return(!(MouseStateBef_.Button_[idx] & 0x80) && MouseState_.Button_[idx] & 0x80) ;
		}
		/**
		 * �}�E�X�̃{�^���������ꂽ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButtonDown(MouseButtonE idx)
		{
			return(!(MouseStateBef_.Button_[idx] & 0x80) && MouseState_.Button_[idx] & 0x80) ;
		}

		/**
		 * �}�E�X�̃{�^�����͂Ȃ��ꂽ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButtonUp(int idx)
		{
			return (MouseStateBef_.Button_[idx] & 0x80 && !(MouseState_.Button_[idx] & 0x80)) ;
		}
		/**
		 * �}�E�X�̃{�^�����͂Ȃ��ꂽ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	idx	The index.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetMoudeButtonUp(MouseButtonE idx)
		{
			return(MouseStateBef_.Button_[idx] & 0x80 && !(MouseState_.Button_[idx] & 0x80)) ;
		}

		/**
		 * Gets key button.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	key	The key.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetKeyButton(KeyCodeE key)
		{
			return (bool)(Keyboard_[key] & 0x80);
		}

		/**
		 * Gets key button down.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	key	The key.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetKeyButtonDown(KeyCodeE key)
		{
			return (bool)(!(KeyboardBef_[key] & 0x80) && Keyboard_[key] & 0x80);
		}

		/**
		 * Gets key button up.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @param	key	The key.
		 *
		 * @return	True if it succeeds, false if it fails.
		 */
		bool GetKeyButtonUp(KeyCodeE key)
		{
			return (bool)(KeyboardBef_[key] & 0x80 && !(Keyboard_[key] & 0x80));
		}

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/09
		 *
		 * @return	The instance.
		 */
		inline static CInput& GetInstance()
		{
			static CInput instance;
			return instance;
		}

	private:

		/**
		 * �}�E�X������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param hWnd Handle of the window.
		 */
		void InitMouse(HWND hWnd);

		/**
		 * �L�[�{�[�h������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param hWnd Handle of the window.
		 */
		void InitKeyboard(HWND hWnd);

	private:
		/** ���݂̃}�E�X�X�e�[�^�X. */
		MouseStateS MouseState_;
		/** 1�t���[���O�̃}�E�X�X�e�[�^�X. */
		MouseStateS MouseStateBef_;
		/**   
	     * �}�E�X�̃|�W�V����.  
		 * �N���C�A���g�̍����� 0,0 �ɂȂ�.
		 */
		POINT MousePos_;
		/** ���݂̃L�[�{�[�h�X�e�[�^�X. */
		BYTE Keyboard_[256];
		/** ���O�̃L�[�{�[�h�X�e�[�^�X. */
		BYTE KeyboardBef_[256];
		/** �}�E�X�f�o�C�X. */
		IDirectInputDevice8* DInputMouse_ = nullptr;
		/** �L�[�{�[�h�f�o�C�X. */
		IDirectInputDevice8* DInputKeyboard_ = nullptr;
		/** �Ȃ��ɂ��ꂥ. */
		IDirectInput8* DInput_ = nullptr;
		/** �L�[�{�[�h���g�p����. */
		bool isKeyboard_;
		/** �}�E�X���g�p����. */
		bool isMouse_;
	};

	/**
	 * �C���v�b�g�N���X�擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CInput.
	 */
	inline static CInput& Input()
	{
		return CInput::GetInstance();
	}

}// namespace nkEgnie