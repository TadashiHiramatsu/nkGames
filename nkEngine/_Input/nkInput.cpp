/**
 * @file	_Input\nkInput.cpp
 *
 * DirectInput�N���X�̎���.
 */
#include"nkEngine/nkstdafx.h"
#include"nkInput.h"

namespace nkEngine
{
		
	/**
	 * ������.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param hWnd Handle of the window.
	 *
	 * @return A hResult.
	 */
	HRESULT CInput::Init(HWND hWnd)
	{
		HRESULT hr;

		if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&DInput_, NULL)))
		{
			return hr;
		}

		//�}�E�X�̏�����
		InitMouse(hWnd);

		//�L�[�{�[�h�̏�����
		InitKeyboard(hWnd);

		return S_OK;
	}

	/**
	 * �}�E�X�̏�����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param hWnd Handle of the window.
	 */
	void CInput::InitMouse(HWND hWnd)
	{
		DIOBJECTDATAFORMAT ObjectFormats[] =
		{
			{ &GUID_XAxis, FIELD_OFFSET(MouseStateS, PosX_),    // X axis
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_YAxis, FIELD_OFFSET(MouseStateS, PosY_),    // Y axis
			DIDFT_RELAXIS | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[0]),        // Button 0
			DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[1]),        // Button 1 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 },
			{ &GUID_Button, FIELD_OFFSET(MouseStateS, Button_[2]),        // Button 2 (optional)
			DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 }
		};

		DIDATAFORMAT dfMouse =
		{
			sizeof(DIDATAFORMAT),
			sizeof(DIOBJECTDATAFORMAT),
			DIDF_ABSAXIS,
			sizeof(MouseStateS),
			sizeof(ObjectFormats) / sizeof(DIOBJECTDATAFORMAT),
			ObjectFormats
		};

		DInput_->CreateDevice(GUID_SysMouse, &DInputMouse_, NULL);

		DInputMouse_->SetDataFormat(&dfMouse);

		DInputMouse_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
		DInputMouse_->Acquire();

	}

	/**
	 * �L�[�{�[�h�̏�����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @param hWnd Handle of the window.
	 */
	void CInput::InitKeyboard(HWND hWnd)
	{
		DInput_->CreateDevice(GUID_SysKeyboard,&DInputKeyboard_,NULL);

		DInputKeyboard_->SetDataFormat(&c_dfDIKeyboard);

		DInputKeyboard_->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	/**
	 * �X�V.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CInput::Update()
	{
		HRESULT hr;

		if (isMouse_)
		{
			//�}�E�X�̃|�W�V�������擾
			GetCursorPos(&MousePos_);
			//�N���C�A���g�T�C�Y�ɕύX
			ScreenToClient(Engine().GetHWND(), &MousePos_);

			//1�t���[���O�̌��ʂ��R�s�[
			MouseStateBef_ = MouseState_;
			
			hr = DInputMouse_->GetDeviceState(sizeof(MouseStateS), &MouseState_);
			if (FAILED(hr))
			{
				DInputMouse_->Acquire();
				DInputMouse_->GetDeviceState(sizeof(MouseStateS), &MouseState_);
			}
		}

		if (isKeyboard_)
		{
			//1�t���[���O�̌��ʂ��R�s�[
			memcpy(KeyboardBef_, Keyboard_, 256);

			hr = DInputKeyboard_->GetDeviceState(sizeof(Keyboard_), &Keyboard_);
			if (FAILED(hr))
			{
				DInputKeyboard_->Acquire();
				DInputKeyboard_->GetDeviceState(sizeof(Keyboard_), &Keyboard_);
			}
		}
	}

	/**
	 * ���.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	void CInput::Release()
	{
		if (DInputMouse_)
		{
			DInputMouse_->Unacquire();
		}
		if (DInputKeyboard_)
		{
			DInputKeyboard_->Unacquire();
		}

		SAFE_RELEASE(DInputMouse_);
		SAFE_RELEASE(DInputKeyboard_);
		SAFE_RELEASE(DInput_);
	}

}// namespace nkEngine