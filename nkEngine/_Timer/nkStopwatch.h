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
	class Stopwatch : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		Stopwatch() :
			Freq_(0),
			End_(0),
			Begin_(0),
			Elapsed_(0.0),
			ElapsedMill_(0.0),
			ElapsedMicro_(0.0)
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
			::QueryPerformanceCounter((LARGE_INTEGER*)&Begin_);
		}

		/**
		 * 計測終了.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Stop()
		{
			::QueryPerformanceFrequency((LARGE_INTEGER*)&Freq_);
			::QueryPerformanceCounter((LARGE_INTEGER*)&End_);

			Elapsed_ = double(End_ - Begin_) / Freq_;
			ElapsedMill_ = ElapsedMicro_ * 1000.0;
			ElapsedMicro_ = ElapsedMill_ * 1000.0;
		}

		/**
		 * 経過時間を取得(単位:秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	経過時間(単位:秒).
		 */
		double GetElapsed() const
		{
			return Elapsed_;
		}

		/**
		 * 経過時間を取得(単位:ミリ秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	経過時間(単位:ミリ秒).
		 */
		double GetElapsedMillisecond() const
		{
			return ElapsedMill_;
		}

		/**
		 * 経過時間を取得(単位:マイクロ秒).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	経過時間(単位:マイクロ秒).
		 */
		double GetElapsedMicrosecond() const
		{
			return ElapsedMicro_;
		}

	private:

		/** The frequency. */
		LONGLONG Freq_;
		/** The end. */
		LONGLONG End_;
		/** The begin. */
		LONGLONG Begin_;
		/** 経過時間(単位：秒). */
		double Elapsed_;
		/** 経過時間(単位：ミリ秒). */
		double ElapsedMill_;
		/** 経過時間(単位：マイクロ秒). */
		double ElapsedMicro_;

	};

}// namespace nkEngine