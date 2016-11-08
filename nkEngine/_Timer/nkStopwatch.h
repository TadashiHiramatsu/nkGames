#pragma once


namespace nkEngine
{
	class Stopwatch
	{
	public:
		//�R���X�g���N�^
		Stopwatch()
		{
			freq = 0;
			end = 0;
			begin = 0;
			elapsed = 0.0;
			elapsedMill = 0.0;
			elapsedMicro = 0.0;
		}

		//�f�X�g���N�^
		~Stopwatch() {}

		//�v���J�n
		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)&begin);
		}

		//�v���I��
		void Stop()
		{
			::QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
			::QueryPerformanceCounter((LARGE_INTEGER*)&end);
			elapsed = double(end - begin) / freq;
			elapsedMill = elapsedMicro * 1000.0;
			elapsedMicro = elapsedMill * 1000.0;
		}

		//	�o�ߎ��Ԃ��擾(�P��:�b)
		double GetElapsed() const
		{
			return elapsed;
		}
		//	�o�ߎ��Ԃ��擾(�P��:�~���b)
		double GetElapsedMillisecond() const
		{
			return elapsedMill;
		}
		//	�o�ߎ��Ԃ��擾(�P��:�}�C�N���b)
		double GetElapsedMicrosecond() const
		{
			return elapsedMicro;
		}

	private:
		LONGLONG freq;
		LONGLONG end;
		LONGLONG begin;
		double elapsed;			//�o�ߎ���(�P�ʁF�b)
		double elapsedMill;		//�o�ߎ���(�P�ʁF�~���b)
		double elapsedMicro;	//�o�ߎ���(�P�ʁF�}�C�N���b)
	};
}