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
	//	LONG LeftStick[2]; //0:�c,1:��
	//	LONG RightStick[2]; //0:�c,1:��
	//	BYTE Button[20]; //�܂��킩���
	//	LONG Shoulder[2]; //0:��,1:�E
	//};

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
		LONG GetMovementX()
		{
			return m_MouseState0.PosX - m_MouseState.PosX;
		}

		//Y���̈ړ��ʂ�Ԃ�
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

		//�}�E�X������
		void InitMouse(HWND hWnd);

		//�L�[�{�[�h������
		void InitKeyboard(HWND hWnd);

		//�W���C�X�e�B�b�N������
		//void InitJoystick(HWND hWnd);

		//static BOOL PASCAL EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
		//static BOOL PASCAL EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	private:
		MouseState m_MouseState; //���݂̃}�E�X�X�e�[�^�X
		MouseState m_MouseState0; //���O�̃}�E�X�X�e�[�^�X
		BYTE m_Keyboard[256]; //���݂̃L�[�{�[�h�X�e�[�^�X
		
		//JoystickState m_JoystickState;

		IDirectInputDevice8* m_DInputMouse = nullptr; //�}�E�X�f�o�C�X
		IDirectInputDevice8* m_DInputKeyboard = nullptr; //�L�[�{�[�h�f�o�C�X
		//IDirectInputDevice8* m_DInputJoystick = nullptr; //�W���C�X�e�B�b�N�f�o�C�X
		IDirectInput8* m_DInput = nullptr; //�Ȃ��ɂ��ꂥ

		//DIDEVCAPS m_diDevCaps; // �W���C�X�e�B�b�N�̔\��

		bool m_isKeyboard; //�L�[�{�[�h���g�p����
		bool m_isMouse; //�}�E�X���g�p����
		bool m_isJoystick; //�W���C�X�e�B�b�N���g�p����
	};

	inline static CInput& Input()
	{
		return CInput::GetInstance();
	}
}

