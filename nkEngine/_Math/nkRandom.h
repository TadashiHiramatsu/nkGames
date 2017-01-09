/**
 * @file	_Math\nkRandom.h
 *
 * ランダムクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ランダムクラス.
	 * シングルトンクラス.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/08
	 */
	class CRandom
	{
	private:
		
		/**
		 * コンストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		CRandom() 
		{
		}

		/**
		 * デストラクタ.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 */
		~CRandom() 
		{
		}

	public:

		/**
		 * インスタンスの取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @return	The instance.
		 */
		static CRandom& GetInstance()
		{
			static CRandom instance;
			return instance;
		}

		/**
		 * 乱数を初期化.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @param	seed	The seed.
		 */
		void Init(unsigned long seed)
		{
			mt[0] = seed & 0xffffffffUL;
			for (mti = 1; mti < N; mti++) 
			{
				mt[mti] =
					(1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
				/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
				/* In the previous versions, MSBs of the seed affect   */
				/* only MSBs of the array mt[].                        */
				/* 2002/01/09 modified by Makoto Matsumoto             */
				mt[mti] &= 0xffffffffUL;
				/* for >32 bit machines */
			}
		}

		/**
		 * 符号なし整数型のランダム値を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @return	The random int.
		 */
		__inline unsigned long GetRandInt()
		{
			unsigned long y;
			static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
			/* mag01[x] = x * MATRIX_A  for x=0,1 */

			if (mti >= N) /* generate N words at one time */
			{
				int kk;

				if (mti == N + 1)   /* if init_genrand() has not been called, */
					Init(5489UL); /* a default initial seed is used */

				for (kk = 0; kk < N - M; kk++) {
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				for (; kk < N - 1; kk++) {
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
				mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

				mti = 0;
			}

			y = mt[mti++];

			/* Tempering */
			y ^= (y >> 11);
			y ^= (y << 7) & 0x9d2c5680UL;
			y ^= (y << 15) & 0xefc60000UL;
			y ^= (y >> 18);

			return y;
		}

		/**
		 * 符号付き整数型のランダム値を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @return	The random s int.
		 */
		__inline long GetRandSInt()
		{
			(long)(GetRandInt() >> 1);
		}

		/**
		 * 倍精度小数点型のランダム値を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @return	0.0～1.0のランダム値を返す.
		 */
		__inline double GetRandDouble()
		{
			return GetRandInt()*(1.0 / 4294967295.0);
		}

		/**
		 * 倍精度小数点型のランダム値を取得.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @return	-1.0～1.0のランダム値を返す.
		 */
		__inline double GetRandDouble0()
		{
			return (GetRandInt()*(1.0 / 4294967295.0)) * 2 - 1;
		}

	private:

		/** The long to process. */
		static const unsigned long N = 624;
		/** The long to process. */
		static const unsigned long M = 397;
		/** constant vector a. */
		static const unsigned long MATRIX_A = 0x9908b0dfUL;  
		/** most significant w-r bits. */
		static const unsigned long UPPER_MASK = 0x80000000UL;
		/** least significant r bits. */
		static const unsigned long LOWER_MASK = 0x7fffffffUL; 
		/** the array for the state vector. */
		unsigned long mt[N];
		/**  mti==N+1 means mt[N] is not initialized. */
		int mti = N + 1;

	};

	/**
	 * ランダムクラスの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/08
	 *
	 * @return	A reference to a CRandom.
	 */
	inline static CRandom& Random()
	{
		return CRandom::GetInstance();
	}

}// namespace nkEngine