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
		 * ���X�e�B�b�N��X���̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		float GetStickL_X()
		{
			return LeftStickX_;
		}

		/**
		 * ���X�e�B�b�N��Y���̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		float GetStickL_Y()
		{
			return LeftStickY_;
		}

		/**
		 * �E�X�e�B�b�N��X���̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		float GetStickR_X()
		{
			return RightStickX_;
		}

		/**
		 * �E�X�e�B�b�N��Y���̌X����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		float GetStickR_Y()
		{
			return RightStickY_;
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
		bool IsTrigger(ButtonE button)
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
		BYTE  GetTriggerL()
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
		BYTE  GetTriggerR()
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
		/** ���X�e�B�b�N��X���̓��͗�. */
		float LeftStickX_;
		/** ���X�e�B�b�N��Y���̓��͗�. */
		float LeftStickY_;
		/** �E�X�e�B�b�N��X���̓��͗�. */
		float RightStickX_;
		/** �E�X�e�B�b�N��Y���̓��͗�. */
		float RightStickY_;

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