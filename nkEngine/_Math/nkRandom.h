/**
* @file	_Math\nkRandom.h
*
* ランダムクラスの定義.
*/
#pragma once

#include <time.h>

namespace nkEngine
{

	/**
	* ランダムクラス.
	* シングルトンクラス.
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/08
	*/
	class Random
	{
	public:

		/**
		* 初期化.
		*
		* @author	Hiramatsu
		* @date		2017/01/31
		*/
		static void Start()
		{
			srand((unsigned)time(nullptr));
		}

		//min(この値を含む)とmax(この値を含む)の範囲のランダムなfloat型の数を返します.
		static float Range(float min, float max)
		{
			return min + ((float)rand() * (max - min) / (1.0 + RAND_MAX));
		}

		//min(この値を含む)とmax(この値を含む)の範囲のランダムなint型の数を返します.
		static int Range(int min, int max)
		{
			return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
		}

		//0.0(この値を含む)と1.0(この値を含む)の範囲のランダムな数を返します.
		static double value()
		{
			return rand() * (1.0 / RAND_MAX);
		}

	};

}// namespace nkEngine