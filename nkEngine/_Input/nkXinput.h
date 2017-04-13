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

	/** �R���g���[���̃{�^��. */
	enum class ButtonE
	{
		Up,			//!< ��.
		Down,		//!< ��.
		Left,		//!< ��.
		Right,		//!< �E.
		A,			//!< A�{�^��.
		B,			//!< B�{�^��.
		X,			//!< X�{�^��.
		Y,			//!< Y�{�^��.
		Select,		//!< �Z���N�g�{�^��.
		Start,		//!< �X�^�[�g�{�^��.
		RB1,		//!< RB1�{�^��.
		RB2,		//!< RB2�{�^��.
		RB3,		//!< RB3�{�^��.
		LB1,		//!< LB1�{�^��.
		LB2,		//!< LB2�{�^��.
		LB3,		//!< LB3�{�^��.
		ButtonNum,	//!< �{�^���̐�.
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
	class CXinput : Noncopyable
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
		~CXinput()
		{
		}

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
		 * x:��.y:�c
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		const Vector2& GetLeftStick() const
		{
			return LeftStick_;
		}

		/**
		 * �E�X�e�B�b�N�̌X����.
		 * x:��.y:�c
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0�`1.0�̐��K�����ꂽ�l��Ԃ�.
		 */
		const Vector2& GetRightStick() const
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
		bool IsPress(ButtonE button) const
		{
			return Press_[(int)button] != 0;
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
			return Trigger_[(int)button] != 0;
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

		/** �Q�[���p�b�h�̏��. */
		GamePadStateS GamePad_;
		
		/** �g���K�[���͂̃t���O. */
		int Trigger_[(int)ButtonE::ButtonNum];
		/** press���͂̃t���O. */
		int Press_[(int)ButtonE::ButtonNum];
		
		/** ���g���K�[. */
		BYTE LeftTrigger_ = 0;
		/** �E�g���K�[. */
		BYTE RightTrigger_ = 0;

		/** ���X�e�B�b�N�̓��͗�. */
		Vector2 LeftStick_ = Vector2::Zero;
		
		/** �E�X�e�B�b�N�̓��͗�. */
		Vector2 RightStick_ = Vector2::Zero;

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