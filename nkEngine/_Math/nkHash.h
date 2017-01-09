/**
 * @file	_Math\nkHash.h
 *
 * �n�b�V���N���X.
 */
#pragma once

namespace nkEngine
{

	/**
	 * A hash.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/08
	 */
	class Hash
	{
	public:

		/**
		 * �n�b�V���쐬.
		 *
		 * @author	HiramatsuTadashi
		 * @date	2017/01/08
		 *
		 * @param	string	The string.
		 *
		 * @return	An int.
		 */
		static int MakeHash(const char* string)
		{
			int hash = 0;
			int len = (int)strlen(string);
			for (int i = 0; i < len; i++)
			{
				hash = hash * 37 + string[i];
			}
			return hash;
		}

	};

}// namespace nkEngine