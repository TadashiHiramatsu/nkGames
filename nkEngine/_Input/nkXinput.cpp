/**
 * @file _Input\nkXinput.cpp
 *
 * XInputクラスの実装.
 */
#include"nkEngine/nkstdafx.h"
#include"nkXinput.h"

namespace nkEngine
{
	/**
	 * 仮想ボタンとXBoxコントローラのボタンとの関連付けを表す構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct VirtualPadToXPad 
	{
	public:

		/** 仮想ボタン. */
		ButtonE vButton_;
		/** XBoxコントローラのボタン. */
		DWORD xButton_;
	
	};

	/** The pad to x coordinate pad table[ button num]. */
	const VirtualPadToXPad vPadToXPadTable[ButtonNum] = 
	{
		{ ButtonUp		, XINPUT_GAMEPAD_DPAD_UP		},
		{ ButtonDown	, XINPUT_GAMEPAD_DPAD_DOWN		},
		{ ButtonLeft	, XINPUT_GAMEPAD_DPAD_LEFT		},
		{ ButtonRight	, XINPUT_GAMEPAD_DPAD_RIGHT		},
		{ ButtonA		, XINPUT_GAMEPAD_A				},
		{ ButtonB		, XINPUT_GAMEPAD_B				},
		{ ButtonY		, XINPUT_GAMEPAD_Y				},
		{ ButtonX		, XINPUT_GAMEPAD_X				},
		{ ButtonSelect	, XINPUT_GAMEPAD_BACK			},
		{ ButtonStart	, XINPUT_GAMEPAD_START			},
		{ ButtonRB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
		{ ButtonRB2		, 0								},
		{ ButtonRB3		, XINPUT_GAMEPAD_RIGHT_THUMB	},
		{ ButtonLB1		, XINPUT_GAMEPAD_LEFT_SHOULDER	},
		{ ButtonLB2		, 0								},
		{ ButtonLB3		, XINPUT_GAMEPAD_LEFT_THUMB		},
	};

	/**
	 * 仮想ボタンとキーボードとの関連付けを表す構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct VirtualPadToKeyboard 
	{
	public:

		/** 仮想ボタン. */
		ButtonE vButton_;
		/** キーボードのキーコード. */
		DWORD KeyCoord_;
	};

	/** The pad to keyboard table[ button num]. */
	const VirtualPadToKeyboard vPadToKeyboardTable[ButtonNum] =
	{
		{ ButtonUp		, '8'		},
		{ ButtonDown	, '2'		},
		{ ButtonLeft	, '4'		},
		{ ButtonRight	, '6'		},
		{ ButtonA		, 'J'		},
		{ ButtonB		, 'K'		},
		{ ButtonY		, 'I'		},
		{ ButtonX		, 'O'		},
		{ ButtonSelect	, VK_SPACE	},
		{ ButtonStart	, VK_RETURN },
		{ ButtonRB1		, '7'		},
		{ ButtonRB2		, '8'		},
		{ ButtonRB3		, '9'		},
		{ ButtonLB1		, 'B'		},
		{ ButtonLB2		, 'N'		},
		{ ButtonLB3		, 'M'		},
	};

	/**
	 * コンストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CXinput::CXinput() :
		LeftStickX_(0.0f),
		LeftStickY_(0.0f),
		RightStickX_(0.0f),
		RightStickY_(0.0f),
		LeftTrigger_(0),
		RightTrigger_(0)
	{
		memset(&GamePad_, 0, sizeof(GamePad_));
		memset(Trigger_, 0, sizeof(Trigger_));
		memset(Press_, 0, sizeof(Press_));
	}

	/**
	 * デストラクタ.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CXinput::~CXinput()
	{
	}

	/**
	 * 更新.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CXinput::Update()
	{
		//ゲームパッドのステートを取得
		DWORD result = XInputGetState(0, &GamePad_.State_);

		if (result == ERROR_SUCCESS) 
		{
			//接続されている
			GamePad_.Connected_ = true;

			for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable) 
			{
				if (GamePad_.State_.Gamepad.wButtons & vPadToXPad.xButton_) 
				{
					Trigger_[vPadToXPad.vButton_] = 1 ^ Press_[vPadToXPad.vButton_];
					Press_[vPadToXPad.vButton_] = 1;
				}
				else {
					Trigger_[vPadToXPad.vButton_] = 0;
					Press_[vPadToXPad.vButton_] = 0;
				}
			}

			if ((GamePad_.State_.Gamepad.sThumbLX < INPUT_DEADZONE &&
				GamePad_.State_.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(GamePad_.State_.Gamepad.sThumbLY < INPUT_DEADZONE &&
					GamePad_.State_.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				GamePad_.State_.Gamepad.sThumbLX = 0;
				GamePad_.State_.Gamepad.sThumbLY = 0;
				LeftStickX_ = 0.0f;
				LeftStickY_ = 0.0f;
			}
			else 
			{
				//左スティックの入力量。正規化
				if (GamePad_.State_.Gamepad.sThumbLX > 0) 
				{
					LeftStickX_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbLX) / SHRT_MAX;
				}
				else 
				{
					LeftStickX_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbLX) / -SHRT_MIN;
				}

				if (GamePad_.State_.Gamepad.sThumbLY > 0) 
				{
					LeftStickY_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbLY) / SHRT_MAX;
				}
				else 
				{
					LeftStickY_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbLY) / -SHRT_MIN;
				}
			}

			if ((GamePad_.State_.Gamepad.sThumbRX < INPUT_DEADZONE &&
				GamePad_.State_.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(GamePad_.State_.Gamepad.sThumbRY < INPUT_DEADZONE &&
					GamePad_.State_.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				GamePad_.State_.Gamepad.sThumbRX = 0;
				GamePad_.State_.Gamepad.sThumbRY = 0;
				RightStickX_ = 0.0f;
				RightStickY_ = 0.0f;
			}
			else
			{
				//右スティックの入力量。
				if (GamePad_.State_.Gamepad.sThumbRX > 0) 
				{
					RightStickX_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbRX) / SHRT_MAX;
				}
				else 
				{
					RightStickX_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbRX) / -SHRT_MIN;
				}

				if (GamePad_.State_.Gamepad.sThumbRY > 0)
				{
					RightStickY_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbRY) / SHRT_MAX;
				}
				else 
				{
					RightStickY_ = s_cast<float>(GamePad_.State_.Gamepad.sThumbRY) / -SHRT_MIN;
				}
			}
			LeftTrigger_ = GamePad_.State_.Gamepad.bLeftTrigger;
			RightTrigger_ = GamePad_.State_.Gamepad.bRightTrigger;
		}
		else
		{
			//接続されていない場合はキーボードの入力でエミュレートする。
			if (GamePad_.Connected_) 
			{
				//未接続になった。
				memset(&GamePad_, 0, sizeof(GamePad_));
				memset(Trigger_, 0, sizeof(Trigger_));
				memset(Press_, 0, sizeof(Press_));
			}

			LeftStickX_ = 0.0f;
			LeftStickY_ = 0.0f;
			RightStickX_ = 0.0f;
			RightStickY_ = 0.0f;
			LeftTrigger_ = 0;
			RightTrigger_ = 0;

			if (GetAsyncKeyState(VK_LEFT)) 
			{
				RightStickX_ += -1.0f;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				RightStickX_ += 1.0f;
			}
			if (GetAsyncKeyState(VK_UP))
			{
				RightStickY_ += 1.0f;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				RightStickY_ += -1.0f;
			}

			if (GetAsyncKeyState('A')) 
			{
				LeftStickX_ += -1.0f;
			}
			if (GetAsyncKeyState('D'))
			{
				LeftStickX_ += 1.0f;
			}
			if (GetAsyncKeyState('W'))
			{
				LeftStickY_ += 1.0f;
			}
			if (GetAsyncKeyState('S')) 
			{
				LeftStickY_ += -1.0f;
			}
		
			if (GetAsyncKeyState('1'))
			{
				LeftTrigger_ = 255;
			}
			if (GetAsyncKeyState('3'))
			{
				RightTrigger_ = 255;
			}

			for (const VirtualPadToKeyboard& vPadToKeyboard : vPadToKeyboardTable)
			{
				if (GetAsyncKeyState(vPadToKeyboard.KeyCoord_)) 
				{
					Trigger_[vPadToKeyboard.vButton_] = 1 ^ Press_[vPadToKeyboard.vButton_];
					Press_[vPadToKeyboard.vButton_] = 1;
				}
				else 
				{
					Trigger_[vPadToKeyboard.vButton_] = 0;
					Press_[vPadToKeyboard.vButton_] = 0;
				}
			}
		}
	}

}// namespace nkEngine