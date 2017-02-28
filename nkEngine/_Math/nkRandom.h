/**
* @file	_Math\nkRandom.h
*
* �����_���N���X�̒�`.
*/
#pragma once

#include <time.h>

namespace nkEngine
{

	/**
	* �����_���N���X.
	* �V���O���g���N���X.
	*/
	class CRandom
	{
	private:

		CRandom()
		{
		}

		~CRandom()
		{
		}

	public:

		/**
		* �C���X�^���X���擾.
		*/
		static CRandom& GetInstance()
		{
			static CRandom instance;
			return instance;
		}

		/**
		* min(���̒l���܂�)��max(���̒l���܂�)�͈̔͂̃����_����float�^�̐���Ԃ��܂�.
		*/
		float Range(float min, float max)
		{
			return min + ((float)GetRandInt() * (max - min) / (1.0 + 0xffffffffUL));
		}

		/** 
		* min(���̒l���܂�)��max(���̒l���܂�)�͈̔͂̃����_����int�^�̐���Ԃ��܂�.
		*/
		int Range(int min, int max)
		{
			return min + (GetRandInt() % (max - min + 1));
		}

		/** 
		* 0.0(���̒l���܂�)��1.0(���̒l���܂�)�͈̔͂̃����_���Ȑ���Ԃ��܂�.
		*/
		double value()
		{
			return GetRandInt() * (1.0 / 4294967295.0);
		}

	private:

		/**
		* ������.
		*/
		void Init(unsigned long seed)
		{
			mt[0] = seed & 0xffffffffUL;
			for (mti = 1; mti < N; mti++)
			{
				mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);

				mt[mti] &= 0xffffffffUL;

			}
		}

		/**
		* 0�`0xffffffff�̋[��������Ԃ�.
		*/
		__inline unsigned long GetRandInt()
		{
			unsigned long y;
			static unsigned long mag01[2] = { 0x0UL, MATRIX_A };

			if (mti >= N) 
			{
				int kk;

				if (mti == N + 1)
				{
					Init((unsigned long)time);
				}

				for (kk = 0; kk<N - M; kk++) 
				{
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				for (; kk<N - 1; kk++) 
				{
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
				mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

				mti = 0;
			}

			y = mt[mti++];

			y ^= (y >> 11);
			y ^= (y << 7) & 0x9d2c5680UL;
			y ^= (y << 15) & 0xefc60000UL;
			y ^= (y >> 18);

			return y;
		}

	private:

		static const unsigned long N = 624;
		static const unsigned long M = 397;
		static const unsigned long MATRIX_A = 0x9908b0dfUL;   
		static const unsigned long UPPER_MASK = 0x80000000UL; 
		static const unsigned long LOWER_MASK = 0x7fffffffUL; 
		unsigned long mt[N];
		int mti = N + 1;

	};

	static CRandom& Random()
	{
		return CRandom::GetInstance();
	}

}// namespace nkEngine