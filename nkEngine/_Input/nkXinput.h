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

	/** コントローラのボタン. */
	enum class ButtonE
	{
		Up,			//!< 上.
		Down,		//!< 下.
		Left,		//!< 左.
		Right,		//!< 右.
		A,			//!< Aボタン.
		B,			//!< Bボタン.
		X,			//!< Xボタン.
		Y,			//!< Yボタン.
		Select,		//!< セレクトボタン.
		Start,		//!< スタートボタン.
		RB1,		//!< RB1ボタン.
		RB2,		//!< RB2ボタン.
		RB3,		//!< RB3ボタン.
		LB1,		//!< LB1ボタン.
		LB2,		//!< LB2ボタン.
		LB3,		//!< LB3ボタン.
		ButtonNum,	//!< ボタンの数.
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
	class CXinput : Noncopyable
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
		~CXinput()
		{
		}

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
		 * 左スティックの傾き量.
		 * x:横.y:縦
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		const Vector2& GetLeftStick() const
		{
			return LeftStick_;
		}

		/**
		 * 右スティックの傾き量.
		 * x:横.y:縦
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return -1.0～1.0の正規化された値を返す.
		 */
		const Vector2& GetRightStick() const
		{
			return RightStick_;
		}

		//左スティックの引数のベクトルからの角度を求める
		float GetLeftStickAngle() const
		{
			float angle = D3DXToDegree(atan2f(LeftStick_.y, LeftStick_.x));
			if (angle < 0.0f)
			{
				angle += 360;
			}
			return angle;
		}

		//右スティックの引数のベクトルからの角度を求める
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
		 * ボタンが押されているか.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param button The button.
		 *
		 * @return true:押された,false:押されてない.
		 */
		bool IsPress(ButtonE button) const
		{
			return Press_[(int)button] != 0;
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
		bool IsTrigger(ButtonE button) const
		{
			return Trigger_[(int)button] != 0;
		}

		/**
		 * 左のトリガーの深度.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return 0～255.
		 */
		BYTE  GetTriggerL() const
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
		BYTE  GetTriggerR() const
		{
			return RightTrigger_;
		}

	private:

		/** ゲームパッドの情報. */
		GamePadStateS GamePad_;
		
		/** トリガー入力のフラグ. */
		int Trigger_[(int)ButtonE::ButtonNum];
		/** press入力のフラグ. */
		int Press_[(int)ButtonE::ButtonNum];
		
		/** 左トリガー. */
		BYTE LeftTrigger_ = 0;
		/** 右トリガー. */
		BYTE RightTrigger_ = 0;

		/** 左スティックの入力量. */
		Vector2 LeftStick_ = Vector2::Zero;
		
		/** 右スティックの入力量. */
		Vector2 RightStick_ = Vector2::Zero;

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