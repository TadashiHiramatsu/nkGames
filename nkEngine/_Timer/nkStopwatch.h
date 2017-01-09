/**
 * @file	_Timer\nkStopwatch.h
 *
 * ストップウォッチクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ストップウォッチクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class Stopwatch
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		Stopwatch() :
			freq_(0),
			end_(0),
			begin_(0),
			elapsed_(0.0),
			elapsedMill_(0.0),
			elapsedMicro_(0.0)
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~Stopwatch() 
		{
		}

		/**
		 * 計測開始.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)&begin_);
		}

		/**
		 * 計測終了.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Stop()
		{
			::QueryPerformanceFrequency((LARGE_INTEGER*)&freq_);
			::QueryPerformanceCounter((LARGE_INTEGER*)&end_);

			elapsed_ = double(end_ - begin_) / freq_;
			elapsedMill_ = elapsedMicro_ * 1000.0;
			elapsedMicro_ = elapsedMill_ * 1000.0;
		}

		/**
		 * 経過時間を取得(単位:秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The elapsed.
		 */
		double GetElapsed() const
		{
			return elapsed_;
		}

		/**
		 * 経過時間を取得(単位:ミリ秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The elapsed millisecond.
		 */
		double GetElapsedMillisecond() const
		{
			return elapsedMill_;
		}

		/**
		 * 経過時間を取得(単位:マイクロ秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	The elapsed microsecond.
		 */
		double GetElapsedMicrosecond() const
		{
			return elapsedMicro_;
		}

	private:

		/** The frequency. */
		LONGLONG freq_;
		/** The end. */
		LONGLONG end_;
		/** The begin. */
		LONGLONG begin_;
		/** 経過時間(単位：秒). */
		double elapsed_;
		/** 経過時間(単位：ミリ秒). */
		double elapsedMill_;
		/** 経過時間(単位：マイクロ秒). */
		double elapsedMicro_;

	};

}// namespace nkEngine