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
	*
	* @author	HiramatsuTadashi
	* @date	2017/01/08
	*/
	class Random
	{
	public:

		/**
		* ������.
		*
		* @author	Hiramatsu
		* @date		2017/01/31
		*/
		static void Start()
		{
			srand((unsigned)time(nullptr));
		}

		//min(���̒l���܂�)��max(���̒l���܂�)�͈̔͂̃����_����float�^�̐���Ԃ��܂�.
		static float Range(float min, float max)
		{
			return min + ((float)rand() * (max - min) / (1.0 + RAND_MAX));
		}

		//min(���̒l���܂�)��max(���̒l���܂�)�͈̔͂̃����_����int�^�̐���Ԃ��܂�.
		static int Range(int min, int max)
		{
			return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
		}

		//0.0(���̒l���܂�)��1.0(���̒l���܂�)�͈̔͂̃����_���Ȑ���Ԃ��܂�.
		static double value()
		{
			return rand() * (1.0 / RAND_MAX);
		}

	};

}// namespace nkEngine