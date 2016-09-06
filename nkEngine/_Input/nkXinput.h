#pragma once

namespace nkEngine
{
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

	enum EButton {
		enButtonUp,		//!<上。
		enButtonDown,		//!<下。
		enButtonLeft,		//!<左。
		enButtonRight,		//!<右。
		enButtonA,			//!<Aボタン。
		enButtonB,			//!<Bボタン。
		enButtonX,			//!<Xボタン。
		enButtonY,			//!<Yボタン。
		enButtonSelect,	//!<セレクトボタン。
		enButtonStart,		//!<スタートボタン。
		enButtonRB1,		//!<RB1ボタン。
		enButtonRB2,		//!<RB2ボタン。
		enButtonRB3,		//!<RB3ボタン。
		enButtonLB1,		//!<LB1ボタン。
		enButtonLB2,		//!<LB2ボタン。
		enButtonLB3,		//!<LB3ボタン。
		enButtonNum,	//!<ボタンの数。
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
		
		//コントローラーが刺されているかの判定
		void Update();

		//左スティックのX軸の傾き量
		//return	-1.0～1.0の正規化された値を返す
		short GetStickL_X()
		{
			return m_LeftStickX;
		}

		//左スティックのY軸の傾き量
		//return	-1.0～1.0の正規化された値を返す
		short GetStickL_Y()
		{
			return m_LeftStickY;
		}

		//右スティックのX軸の傾き量
		//return	-1.0～1.0の正規化された値を返す
		short GetStickR_X()
		{
			return m_RightStickX;
		}
		
		//右スティックのY軸の傾き量
		//return	-1.0～1.0の正規化された値を返す
		short GetStickR_Y()
		{
			return m_RightStickY;
		}

		//ボタンが押されているか
		//param[in] どのボタンか
		//return true:押された,false:押されてない
		bool IsPress(EButton button)
		{
			return m_press[button] != 0;
		}

		//ボタンが瞬間的に押されたか
		//param[in] どのボタンか
		//return true:押された,false:押されてない
		bool IsTrigger(EButton button)
		{
			return m_trigger[button] != 0;
		}

		//左のトリガーの深度
		//return 0～255
		BYTE  GetTriggerL()
		{
			return m_LeftTrigger;
		}

		//右のトリガーの深度
		//return 0～255
		BYTE  GetTriggerR()
		{
			return m_RightTrigger;
		}
	private:
		CXinput();
		~CXinput();

	private:
		
		CONTROLER_STATE m_Controllers;
		int m_padNo; //パッド番号。

		int m_trigger[enButtonNum];	//トリガー入力のフラグ。
		int m_press[enButtonNum]; //press入力のフラグ。
		BYTE m_LeftTrigger; //左トリガー
		BYTE m_RightTrigger; //右トリガー
		float m_LeftStickX; //左スティックのX軸の入力量。
		float m_LeftStickY; //左スティックのY軸の入力量。
		float m_RightStickX; //右スティックのX軸の入力量。
		float m_RightStickY; //右スティックのY軸の入力量。
	};
	inline static CXinput& XInput()
	{
		return CXinput::Instance();
	}
}