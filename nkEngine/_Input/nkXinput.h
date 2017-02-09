/**
 * @file _Input\nkXinput.h
 *
 * XInput�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

/**
 * �덷��r��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

	/** Values that represent buttons. */
	enum ButtonE {
		ButtonUp,		//!< ��.
		ButtonDown,		//!< ��.
		ButtonLeft,		//!< ��.
		ButtonRight,	//!< �E.
		ButtonA,		//!< A�{�^��.
		ButtonB,		//!< B�{�^��.
		ButtonX,		//!< X�{�^��.
		ButtonY,		//!< Y�{�^��.
		ButtonSelect,	//!< �Z���N�g�{�^��.
		ButtonStart,	//!< �X�^�[�g�{�^��.
		ButtonRB1,		//!< RB1�{�^��.
		ButtonRB2,		//!< RB2�{�^��.
		ButtonRB3,		//!< RB3�{�^��.
		ButtonLB1,		//!< LB1�{�^��.
		ButtonLB2,		//!< LB2�{�^��.
		ButtonLB3,		//!< LB3�{�^��.
		ButtonNum,	    //!< �{�^���̐�.
	};

	/**
	 * �p�b�h�̃X�e�[�g�\����.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct GamePadStateS
	{
	public:

		/** �Q�[���p�b�h�̃X�e�[�g. */
		XINPUT_STATE State_;
		/** �������܂�Ă��邩. */
		bool Connected_;
	};

	/**
	 * XInput�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CXinput
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CXinput();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CXinput();

	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return A reference to a CXinput.
		 */
		static CXinput& Instance()
		{
			static CXinput instance;
			return instance;
		}

		/**
		 * �X�V.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();
		
		/**
		 * ���X�e�B�b�N�̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		D3DXVECTOR2& GetLeftStick()
		{
			return LeftStick_;
		}

		/**
		 * �E�X�e�B�b�N�̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		D3DXVECTOR2& GetRightStick()
		{
			return RightStick_;
		}

		//���X�e�B�b�N�̈����̃x�N�g������̊p�x�����߂�
		float GetLeftStickAngle() const
		{
			float angle = D3DXToDegree(atan2f(LeftStick_.y, LeftStick_.x));
			if (angle < 0.0f)
			{
				angle += 360;
			}
			return angle;
		}

		//�E�X�e�B�b�N�̈����̃x�N�g������̊p�x�����߂�
		float GetRightStickAngle() const
		{
			float angle = D3DXToDegree(atan2f(RightStick_.y, RightStick_.x));
			if (angle < 0.0f)
			{
				angle += 360;
			}
			return angle;
		}

		/**
		 * �{�^����������Ă��邩.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param button The button.
		 *
		 * @return true:�����ꂽ,false:������ĂȂ�.
		 */
		bool IsPress(ButtonE button)
		{
			return Press_[button] != 0;
		}

		/**
		 * �{�^�����u�ԓI�ɉ����ꂽ��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param button The button.
		 *
		 * @return true:�����ꂽ,false:������ĂȂ�.
		 */
		bool IsTrigger(ButtonE button) const
		{
			return Trigger_[button] != 0;
		}

		/**
		 * ���̃g���K�[�̐[�x.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return 0�`255.
		 */
		BYTE  GetTriggerL() const
		{
			return LeftTrigger_;
		}

		/**
		 * �E�̃g���K�[�̐[�x.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return 0�`255.
		 */
		BYTE  GetTriggerR() const
		{
			return RightTrigger_;
		}

	private:

		/** The game pad. */
		GamePadStateS GamePad_;
		
		/** �g���K�[���͂̃t���O. */
		int Trigger_[ButtonNum];
		/** press���͂̃t���O. */
		int Press_[ButtonNum];
		
		/** ���g���K�[. */
		BYTE LeftTrigger_;
		/** �E�g���K�[. */
		BYTE RightTrigger_;

		/** ���X�e�B�b�N�̓��͗�. */
		D3DXVECTOR2 LeftStick_;
		
		/** �E�X�e�B�b�N�̓��͗�. */
		D3DXVECTOR2 RightStick_;

	};

	/**
	 * XInput�N���X�̎�擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CXinput.
	 */
	inline static CXinput& XInput()
	{
		return CXinput::Instance();
	}

}// namespace nkEngine