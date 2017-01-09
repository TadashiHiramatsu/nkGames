/**
 * @file	_Timer\nkTime.h
 *
 * タイムクラスの定義.
 */
#pragma once

#include"nkStopwatch.h"

namespace nkEngine
{
	/**
	 * タイムクラス.
	 * シングルトンクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class CTime
	{
	private:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		CTime() :
			FrameDeltaTime_(0.0f),
			isReady_(false)
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~CTime()
		{
		}

	public:

		/**
		 * インスタンスを取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The instance.
		 */
		static CTime& GetInstance()
		{
			static CTime instance;
			return instance;
		}

		/**
		 * 1フレームの経過時間を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	A float.
		 */
		float DeltaTime() const
		{
			return min(1.0f / 10.0f, FrameDeltaTime_);
		}

		/**
		 * 更新.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Update()
		{
			if (isReady_) {
				sw_.Stop();
				FrameDeltaTime_ = s_cast<float>(sw_.GetElapsed());
			}
			sw_.Start();
			isReady_ = true;
		}

	private:
		/** 1フレームの経過時間. */
		float FrameDeltaTime_;
		/** ストップウォッチ. */
		Stopwatch sw_;
		/** 計測が始まっているかフラグ. */
		bool isReady_;
	};

	/**
	 * タイムクラスのインスタンスを取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	インスタンス.
	 */
	static CTime& Time()
	{
		return CTime::GetInstance();
	}

}// namespace nkEngine