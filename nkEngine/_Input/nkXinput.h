/**
 * @file _Input\nkXinput.h
 *
 * XInputクラスの定義.
 */
#pragma once

namespace nkEngine
{

/**
 * 誤差を排除.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

	/** Values that represent buttons. */
	enum ButtonE {
		ButtonUp,		//!< 上.
		ButtonDown,		//!< 下.
		ButtonLeft,		//!< 左.
		ButtonRight,	//!< 右.
		ButtonA,		//!< Aボタン.
		ButtonB,		//!< Bボタン.
		ButtonX,		//!< Xボタン.
		ButtonY,		//!< Yボタン.
		ButtonSelect,	//!< セレクトボタン.
		ButtonStart,	//!< スタートボタン.
		ButtonRB1,		//!< RB1ボタン.
		ButtonRB2,		//!< RB2ボタン.
		ButtonRB3,		//!< RB3ボタン.
		ButtonLB1,		//!< LB1ボタン.
		ButtonLB2,		//!< LB2ボタン.
		ButtonLB3,		//!< LB3ボタン.
		ButtonNum,	    //!< ボタンの数.
	};

	/**
	 * パッドのステート構造体.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	struct GamePadStateS
	{
	public:

		/** ゲームパッドのステート. */
		XINPUT_STATE State_;
		/** 差し込まれているか. */
		bool Connected_;
	};

	/**
	 * XInputクラス.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CXinput
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CXinput();

		/**
		 * デストラクタ.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CXinput();

	public:

		/**
		 * インスタンスの取得.
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
		 * 更新.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Update();
		
		/**
		 * 左スティックのX軸の傾き量.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		float GetStickL_X()
		{
			return LeftStickX_;
		}

		/**
		 * 左スティックのY軸の傾き量.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		float GetStickL_Y()
		{
			return LeftStickY_;
		}

		/**
		 * 右スティックのX軸の傾き量.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		float GetStickR_X()
		{
			return RightStickX_;
		}

		/**
		 * 右スティックのY軸の傾き量.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		float GetStickR_Y()
		{
			return RightStickY_;
		}

		/**
		 * ボタンが押されているか.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param button The button.
		 *
		 * @return true:押された,false:押されてない.
		 */
		bool IsPress(ButtonE button)
		{
			return Press_[button] != 0;
		}

		/**
		 * ボタンが瞬間的に押されたか.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param button The button.
		 *
		 * @return true:押された,false:押されてない.
		 */
		bool IsTrigger(ButtonE button)
		{
			return Trigger_[button] != 0;
		}

		/**
		 * 左のトリガーの深度.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return 0～255.
		 */
		BYTE  GetTriggerL()
		{
			return LeftTrigger_;
		}

		/**
		 * 右のトリガーの深度.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return 0～255.
		 */
		BYTE  GetTriggerR()
		{
			return RightTrigger_;
		}

	private:

		/** The game pad. */
		GamePadStateS GamePad_;
		/** トリガー入力のフラグ. */
		int Trigger_[ButtonNum];
		/** press入力のフラグ. */
		int Press_[ButtonNum];
		/** 左トリガー. */
		BYTE LeftTrigger_;
		/** 右トリガー. */
		BYTE RightTrigger_;
		/** 左スティックのX軸の入力量. */
		float LeftStickX_;
		/** 左スティックのY軸の入力量. */
		float LeftStickY_;
		/** 右スティックのX軸の入力量. */
		float RightStickX_;
		/** 右スティックのY軸の入力量. */
		float RightStickY_;

	};

	/**
	 * XInputクラスの首取得.
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