#pragma once

namespace nkEngine
{
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

	enum EButton {
		enButtonUp,		//!<��B
		enButtonDown,		//!<���B
		enButtonLeft,		//!<���B
		enButtonRight,		//!<�E�B
		enButtonA,			//!<A�{�^���B
		enButtonB,			//!<B�{�^���B
		enButtonX,			//!<X�{�^���B
		enButtonY,			//!<Y�{�^���B
		enButtonSelect,	//!<�Z���N�g�{�^���B
		enButtonStart,		//!<�X�^�[�g�{�^���B
		enButtonRB1,		//!<RB1�{�^���B
		enButtonRB2,		//!<RB2�{�^���B
		enButtonRB3,		//!<RB3�{�^���B
		enButtonLB1,		//!<LB1�{�^���B
		enButtonLB2,		//!<LB2�{�^���B
		enButtonLB3,		//!<LB3�{�^���B
		enButtonNum,	//!<�{�^���̐��B
	};

	struct CONTROLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};

	class CXinput
	{
	public:
		static CXinput& Instance()
		{
			static CXinput instance;
			return instance;
		}
		
		//�R���g���[���[���h����Ă��邩�̔���
		void Update();

		//���X�e�B�b�N��X���̌X����
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ�
		short GetStickL_X()
		{
			return m_LeftStickX;
		}

		//���X�e�B�b�N��Y���̌X����
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ�
		short GetStickL_Y()
		{
			return m_LeftStickY;
		}

		//�E�X�e�B�b�N��X���̌X����
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ�
		short GetStickR_X()
		{
			return m_RightStickX;
		}
		
		//�E�X�e�B�b�N��Y���̌X����
		//return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ�
		short GetStickR_Y()
		{
			return m_RightStickY;
		}

		//�{�^����������Ă��邩
		//param[in] �ǂ̃{�^����
		//return true:�����ꂽ,false:������ĂȂ�
		bool IsPress(EButton button)
		{
			return m_press[button] != 0;
		}

		//�{�^�����u�ԓI�ɉ����ꂽ��
		//param[in] �ǂ̃{�^����
		//return true:�����ꂽ,false:������ĂȂ�
		bool IsTrigger(EButton button)
		{
			return m_trigger[button] != 0;
		}

		//���̃g���K�[�̐[�x
		//return 0�`255
		BYTE  GetTriggerL()
		{
			return m_LeftTrigger;
		}

		//�E�̃g���K�[�̐[�x
		//return 0�`255
		BYTE  GetTriggerR()
		{
			return m_RightTrigger;
		}
	private:
		CXinput();
		~CXinput();

	private:
		
		CONTROLER_STATE m_Controllers;
		int m_padNo; //�p�b�h�ԍ��B

		int m_trigger[enButtonNum];	//�g���K�[���͂̃t���O�B
		int m_press[enButtonNum]; //press���͂̃t���O�B
		BYTE m_LeftTrigger; //���g���K�[
		BYTE m_RightTrigger; //�E�g���K�[
		float m_LeftStickX; //���X�e�B�b�N��X���̓��͗ʁB
		float m_LeftStickY; //���X�e�B�b�N��Y���̓��͗ʁB
		float m_RightStickX; //�E�X�e�B�b�N��X���̓��͗ʁB
		float m_RightStickY; //�E�X�e�B�b�N��Y���̓��͗ʁB
	};
	inline static CXinput& XInput()
	{
		return CXinput::Instance();
	}
}