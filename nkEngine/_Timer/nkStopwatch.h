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
	class Stopwatch : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
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
			::QueryPerformanceCounter((LARGE_INTEGER*)&Begin_);
		}

		/**
		 * �v���I��.
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
		 * �o�ߎ��Ԃ��擾(�P��:�b).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	�o�ߎ���(�P��:�b).
		 */
		double GetElapsed() const
		{
			return Elapsed_;
		}

		/**
		 * �o�ߎ��Ԃ��擾(�P��:�~���b).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	�o�ߎ���(�P��:�~���b).
		 */
		double GetElapsedMillisecond() const
		{
			return ElapsedMill_;
		}

		/**
		 * �o�ߎ��Ԃ��擾(�P��:�}�C�N���b).
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/07
		 *
		 * @return	�o�ߎ���(�P��:�}�C�N���b).
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
		/** �o�ߎ���(�P�ʁF�b). */
		double Elapsed_;
		/** �o�ߎ���(�P�ʁF�~���b). */
		double ElapsedMill_;
		/** �o�ߎ���(�P�ʁF�}�C�N���b). */
		double ElapsedMicro_;

	};

}// namespace nkEngine