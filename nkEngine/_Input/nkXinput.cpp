/**
 * @file _Input\nkXinput.cpp
 *
 * XInput�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkXinput.h"

namespace nkEngine
{
	/**
	 * ���z�{�^����XBox�R���g���[���̃{�^���Ƃ̊֘A�t����\���\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct VirtualPadToXPad 
	{
	public:

		/** ���z�{�^��. */
		ButtonE vButton_;
		/** XBox�R���g���[���̃{�^��. */
		DWORD xButton_;
	
	};

	/** The pad to x coordinate pad table[ button num]. */
	const VirtualPadToXPad vPadToXPadTable[(int)ButtonE::ButtonNum] = 
	{
		{ ButtonE::Up		, XINPUT_GAMEPAD_DPAD_UP		},
		{ ButtonE::Down		, XINPUT_GAMEPAD_DPAD_DOWN		},
		{ ButtonE::Left		, XINPUT_GAMEPAD_DPAD_LEFT		},
		{ ButtonE::Right	, XINPUT_GAMEPAD_DPAD_RIGHT		},
		{ ButtonE::A		, XINPUT_GAMEPAD_A				},
		{ ButtonE::B		, XINPUT_GAMEPAD_B				},
		{ ButtonE::Y		, XINPUT_GAMEPAD_Y				},
		{ ButtonE::X		, XINPUT_GAMEPAD_X				},
		{ ButtonE::Select	, XINPUT_GAMEPAD_BACK			},
		{ ButtonE::Start	, XINPUT_GAMEPAD_START			},
		{ ButtonE::RB1		, XINPUT_GAMEPAD_RIGHT_SHOULDER },
		{ ButtonE::RB2		, 0								},
		{ ButtonE::RB3		, XINPUT_GAMEPAD_RIGHT_THUMB	},
		{ ButtonE::LB1		, XINPUT_GAMEPAD_LEFT_SHOULDER	},
		{ ButtonE::LB2		, 0								},
		{ ButtonE::LB3		, XINPUT_GAMEPAD_LEFT_THUMB		},
	};

	/**
	 * ���z�{�^���ƃL�[�{�[�h�Ƃ̊֘A�t����\���\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct VirtualPadToKeyboard 
	{
	public:

		/** ���z�{�^��. */
		ButtonE vButton_;
		/** �L�[�{�[�h�̃L�[�R�[�h. */
		DWORD KeyCoord_;

	};

	/** The pad to keyboard table[ button num]. */
	const VirtualPadToKeyboard vPadToKeyboardTable[(int)ButtonE::ButtonNum] =
	{
		{ ButtonE::Up		, '8'		},
		{ ButtonE::Down		, '2'		},
		{ ButtonE::Left		, '4'		},
		{ ButtonE::Right	, '6'		},
		{ ButtonE::A		, 'J'		},
		{ ButtonE::B		, 'K'		},
		{ ButtonE::Y		, 'I'		},
		{ ButtonE::X		, 'O'		},
		{ ButtonE::Select	, VK_SPACE	},
		{ ButtonE::Start	, VK_RETURN },
		{ ButtonE::RB1		, '7'		},
		{ ButtonE::RB2		, '8'		},
		{ ButtonE::RB3		, '9'		},
		{ ButtonE::LB1		, 'B'		},
		{ ButtonE::LB2		, 'N'		},
		{ ButtonE::LB3		, 'M'		},
	};

	/**
	 * �R���X�g���N�^.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	CXinput::CXinput()
	{
		memset(&GamePad_, 0, sizeof(GamePad_));
		memset(Trigger_, 0, sizeof(Trigger_));
		memset(Press_, 0, sizeof(Press_));
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CXinput::Update()
	{
		//�Q�[���p�b�h�̃X�e�[�g���擾
		DWORD result = XInputGetState(0, &GamePad_.State_);

		if (result == ERROR_SUCCESS)
		{
			//�ڑ�����Ă���
			GamePad_.Connected_ = true;

			for (const VirtualPadToXPad& vPadToXPad : vPadToXPadTable)
			{
				if (GamePad_.State_.Gamepad.wButtons & vPadToXPad.xButton_)
				{
					Trigger_[(int)vPadToXPad.vButton_] = 1 ^ Press_[(int)vPadToXPad.vButton_];
					Press_[(int)vPadToXPad.vButton_] = 1;
				}
				else {
					Trigger_[(int)vPadToXPad.vButton_] = 0;
					Press_[(int)vPadToXPad.vButton_] = 0;
				}
			}

			if ((GamePad_.State_.Gamepad.sThumbLX < INPUT_DEADZONE &&
				GamePad_.State_.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(GamePad_.State_.Gamepad.sThumbLY < INPUT_DEADZONE &&
					GamePad_.State_.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				GamePad_.State_.Gamepad.sThumbLX = 0;
				GamePad_.State_.Gamepad.sThumbLY = 0;
				LeftStick_ = Vector2::Zero;
			}
			else
			{
				//���X�e�B�b�N�̓��͗ʁB���K��
				if (GamePad_.State_.Gamepad.sThumbLX > 0)
				{
					LeftStick_.x = s_cast<float>(GamePad_.State_.Gamepad.sThumbLX) / SHRT_MAX;
				}
				else
				{
					LeftStick_.x = s_cast<float>(GamePad_.State_.Gamepad.sThumbLX) / -SHRT_MIN;
				}

				if (GamePad_.State_.Gamepad.sThumbLY > 0)
				{
					LeftStick_.y = s_cast<float>(GamePad_.State_.Gamepad.sThumbLY) / SHRT_MAX;
				}
				else
				{
					LeftStick_.y = s_cast<float>(GamePad_.State_.Gamepad.sThumbLY) / -SHRT_MIN;
				}
			}

			if ((GamePad_.State_.Gamepad.sThumbRX < INPUT_DEADZONE &&
				GamePad_.State_.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(GamePad_.State_.Gamepad.sThumbRY < INPUT_DEADZONE &&
					GamePad_.State_.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				GamePad_.State_.Gamepad.sThumbRX = 0;
				GamePad_.State_.Gamepad.sThumbRY = 0;
				RightStick_ = Vector2::Zero;
			}
			else
			{
				//�E�X�e�B�b�N�̓��͗ʁB
				if (GamePad_.State_.Gamepad.sThumbRX > 0)
				{
					RightStick_.x = s_cast<float>(GamePad_.State_.Gamepad.sThumbRX) / SHRT_MAX;
				}
				else
				{
					RightStick_.x = s_cast<float>(GamePad_.State_.Gamepad.sThumbRX) / -SHRT_MIN;
				}

				if (GamePad_.State_.Gamepad.sThumbRY > 0)
				{
					RightStick_.y = s_cast<float>(GamePad_.State_.Gamepad.sThumbRY) / SHRT_MAX;
				}
				else
				{
					RightStick_.y = s_cast<float>(GamePad_.State_.Gamepad.sThumbRY) / -SHRT_MIN;
				}
			}
			
			LeftTrigger_ = GamePad_.State_.Gamepad.bLeftTrigger;
			RightTrigger_ = GamePad_.State_.Gamepad.bRightTrigger;

		}
		else
		{
			//�ڑ�����Ă��Ȃ��ꍇ�̓L�[�{�[�h�̓��͂ŃG�~�����[�g����B
			if (GamePad_.Connected_)
			{
				//���ڑ��ɂȂ����B
				memset(&GamePad_, 0, sizeof(GamePad_));
				memset(Trigger_, 0, sizeof(Trigger_));
				memset(Press_, 0, sizeof(Press_));
			}

			LeftStick_ = Vector2::Zero;
			RightStick_ = Vector2::Zero;
			LeftTrigger_ = 0;
			RightTrigger_ = 0;

			if (GetAsyncKeyState(VK_LEFT))
			{
				RightStick_.x += -1.0f;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				RightStick_.x += 1.0f;
			}
			if (GetAsyncKeyState(VK_UP))
			{
				RightStick_.y += 1.0f;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				RightStick_.y += -1.0f;
			}

			if (GetAsyncKeyState('A'))
			{
				LeftStick_.x += -1.0f;
			}
			if (GetAsyncKeyState('D'))
			{
				LeftStick_.x += 1.0f;
			}
			if (GetAsyncKeyState('W'))
			{
				LeftStick_.y += 1.0f;
			}
			if (GetAsyncKeyState('S'))
			{
				LeftStick_.y += -1.0f;
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
					Trigger_[(int)vPadToKeyboard.vButton_] = 1 ^ Press_[(int)vPadToKeyboard.vButton_];
					Press_[(int)vPadToKeyboard.vButton_] = 1;
				}
				else
				{
					Trigger_[(int)vPadToKeyboard.vButton_] = 0;
					Press_[(int)vPadToKeyboard.vButton_] = 0;
				}
			}

		}
	}

}// namespace nkEngine