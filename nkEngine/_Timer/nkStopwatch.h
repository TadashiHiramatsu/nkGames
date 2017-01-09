/**
 * @file	_Timer\nkStopwatch.h
 *
 * �X�g�b�v�E�H�b�`�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �X�g�b�v�E�H�b�`�N���X.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 */
	class Stopwatch
	{
	public:

		/**
		 * �R���X�g���N�^.
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
		 * �f�X�g���N�^.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		~Stopwatch() 
		{
		}

		/**
		 * �v���J�n.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 */
		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)&begin_);
		}

		/**
		 * �v���I��.
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
		 * �o�ߎ��Ԃ��擾(�P��:�b).
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
		 * �o�ߎ��Ԃ��擾(�P��:�~���b).
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
		 * �o�ߎ��Ԃ��擾(�P��:�}�C�N���b).
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
		/** �o�ߎ���(�P�ʁF�b). */
		double elapsed_;
		/** �o�ߎ���(�P�ʁF�~���b). */
		double elapsedMill_;
		/** �o�ߎ���(�P�ʁF�}�C�N���b). */
		double elapsedMicro_;

	};

}// namespace nkEngine